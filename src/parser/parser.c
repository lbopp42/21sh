/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:10:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/26 16:38:42 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isio_file(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	(void)nb_tok;
	if (tok_lst->type == LESS && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == LESSAND && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == GREAT && tok_lst->next->type == WORD)
		return (mv + 2);
	else if (tok_lst->type == GREATAND && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == DGREAT && tok_lst->next->type == WORD)
			return (mv + 2);
	return (0);
}

/*
**	nb_tok - tok_lst->i >= 2:
**	This is use to check if we have enought token to use the function
*/

int	isio_redirect(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (nb_tok - tmp >= 2 && (tmp = isio_file(tok_lst, nb_tok, 0)))
		return (mv + tmp);
	else if (tok_lst->type == IO_NUMBER &&
			(mv = isio_file(tok_lst, nb_tok, 1)))
			return (mv + tmp);
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
			return (2 + mv);
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
			return (3 + mv);
	return (0);
}


/*
**	The static [i] is here to avoid an infinity loop
**	4 * i - (i - 1) : this is to avoid an infinity loop too
**	-> It will begin with 3 and increase 2 by 2
*/

int	iscmd_prefix(t_token *tok_lst, int nb_tok, int mv, int mode)
{
	static int i = 0;
	int	tmp;

	tmp = mv;
	if (mode == 1)
		i = 0;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	i++;
	if (nb_tok - mv >= 4 * i - (i - 1) && (mv = iscmd_prefix(tok_lst, nb_tok, 0, 2)) &&
			tok_lst->next && (mv = isio_redirect(tok_lst, nb_tok, mv)))
	{
		return (mv);
	}
	else if ((mv = isio_redirect(tok_lst, nb_tok, 0)))
	{
		return (mv);
	}
	return (0);
}

int	is_word(t_token *tok_lst, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == WORD)
		return (mv + 1);
	else
		return (0);
}

int	is_simplecmd(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)) && (mv = is_word(tok_lst, mv)) &&
			(mv = iscmd_prefix(tok_lst, nb_tok, mv, 1)))
	{
		return (mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)) && (mv = is_word(tok_lst, mv)))
	{
		return (mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)))
		return (mv);
	else if (tok_lst->type == WORD && tok_lst->next &&
			(mv = iscmd_prefix(tok_lst->next, nb_tok, 1, 1)))
		return (mv + 1);
	else if (tok_lst->type == WORD)
		return (1);
	return (0);
}

int	main(void)
{
	t_token	*tok_lst;
	int	nb_tok;
	int	mv;

	mv = 0;
	nb_tok = 3;
	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = IO_NUMBER;
	tok_lst->content = ft_strdup("1");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = GREAT;
	tok_lst->next->content = ft_strdup(">");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->i = 2;
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("lol");
	tok_lst->next->next->next = NULL;/*(t_token*)ft_memalloc(sizeof(t_token));//NULL;
	tok_lst->next->next->next->i = 3;
	tok_lst->next->next->next->type = WORD;
	tok_lst->next->next->next->content = ft_strdup("lol");
	tok_lst->next->next->next->next = NULL;*/
	printf("Result = %d\n", is_simplecmd(tok_lst, nb_tok, mv));
}
