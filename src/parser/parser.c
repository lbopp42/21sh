/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:10:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/26 15:22:03 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isio_file(t_token *tok_lst, int nb_tok, int *max, int mv)
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
	tmp = mv;
	(void)nb_tok;
	if (tok_lst->type == LESS && tok_lst->next->type == WORD)
	{
		if (mv + 2 - 1 > *max)
			*max = mv + 2 - 1;
			return (mv + 2);
	}
	else if (tok_lst->type == LESSAND && tok_lst->next->type == WORD)
	{
		if (mv + 2 - 1 > *max)
			*max = mv + 2 - 1;
			return (mv + 2);
	}
	else if (tok_lst->type == GREAT && tok_lst->next->type == WORD)
	{
		if (mv + 2 - 1 > *max)
			*max = mv + 2 - 1;
		return (mv + 2);
	}
	else if (tok_lst->type == GREATAND && tok_lst->next->type == WORD)
	{
		if (mv + 2 - 1 > *max)
			*max = mv + 2 - 1;
			return (mv + 2);
	}
	else if (tok_lst->type == DGREAT && tok_lst->next->type == WORD)
	{
		if (mv + 2 - 1 > *max)
			*max = mv + 2;
			return (mv + 2);
	}
	return (0);
}

/*
**	nb_tok - tok_lst->i >= 2:
**	This is use to check if we have enought token to use the function
*/

int	isio_redirect(t_token *tok_lst, int nb_tok, int *max, int mv)
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
	if (nb_tok - tmp >= 2 && (tmp = isio_file(tok_lst, nb_tok, max, 0)))
	{
		if (mv + tmp - 1 > *max)
			*max = mv + tmp - 1;
		return (mv + tmp);
	}
	else if (tok_lst->type == IO_NUMBER &&
			(mv = isio_file(tok_lst, nb_tok, max, 1)))
	{
		if (mv - 1 > *max)
			*max = mv - 1;
			return (mv + tmp);
	}
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
	{
		if (2 + mv - 1 > *max)
			*max = 2 + mv - 1;
			return (2 + mv);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
	{
		if (3 + mv - 1 > *max)
			*max = 3 + mv - 1;
			return (3 + mv);
	}
	return (0);
}


/*
**	The static [i] is here to avoid an infinity loop
**	4 * i - (i - 1) : this is to avoid an infinity loop too
**	-> It will begin with 3 and increase 2 by 2
*/

int	iscmd_prefix(t_token *tok_lst, int nb_tok, int *max, int mv)
{
	static int i = 0;
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
	i++;
	if (nb_tok - tmp >= 4 * i - (i - 1) && (tmp = iscmd_prefix(tok_lst, nb_tok, max, 0)) &&
			tok_lst->next && (mv = isio_redirect(tok_lst, nb_tok, max, tmp)))
	{
		if (mv - 1 > *max)
			*max = mv - 1;
			return (mv);
	}
	else if ((mv = isio_redirect(tok_lst, nb_tok, max, tmp)))
	{
		if (mv - 1 > *max)
			*max = mv - 1;
			return (mv);
	}
	return (0);
}

int	main(void)
{
	t_token	*tok_lst;
	int	nb_tok;
	int	max;
	int	mv;

	max = 0;
	mv = 0;
	nb_tok = 4;
	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = DGREAT;
	tok_lst->content = ft_strdup(">>");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = WORD;
	tok_lst->next->content = ft_strdup("ls");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->i = 2;
	tok_lst->next->next->type = DLESS;
	tok_lst->next->next->content = ft_strdup("<<");
	tok_lst->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));//NULL;
	tok_lst->next->next->next->i = 3;
	tok_lst->next->next->next->type = WORD;
	tok_lst->next->next->next->content = ft_strdup("lol");
	tok_lst->next->next->next->next = NULL;
	printf("Result = %d et max = %d\n", iscmd_prefix(tok_lst, nb_tok, &max, mv), max);
}

/*int	is_simplecmd(t_token *tok_lst, int nb_tok, int *max)
{
	int	mv;

	mv = 0;
	if ((mv = iscmd_prefix(tok_lst, nb_tok, max, mv)) && tok_lst->next &&
			tok_lst->next->type == WORD && tok_lst->next->next &&
			(mv = iscmd_prefix(tok_lst, nb_tok, max, mv + 1)))
	{
		if (mv + 1 - 1 > *max)
			*max = mv + 1 - 1;
			return (mv + 1);
	}
	else if (printf("ON PASSE\n") && (mv = iscmd_prefix(tok_lst, nb_tok, max, 0)) && tok_lst->next->type &&
			tok_lst->next->type == WORD)
	{
		printf("C'est bien la, et i = %d\n", tok_lst->next->i);
		if (mv + 1 - 1 > *max)
			*max = mv + 1 - 1;
		printf("max = %d\n", *max);
			return (mv + 1);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, max, 0)))
	{
		if (mv - 1 > *max)
			*max = mv - 1;
			return (mv);
	}
	else if (tok_lst->type == WORD && tok_lst->next &&
			(mv = iscmd_prefix(tok_lst->next, nb_tok, max, 0)))
	{
		if (mv + 1 - 1 > *max)
			*max = mv + 1 - 1;
			return (mv + 1);
	}
	else if (tok_lst->type == WORD)
	{
		if (1 - 1 > *max)
			*max = 1 - 1;
			return (1);
	}
	return (0);
}*/
