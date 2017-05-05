/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:10:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 10:00:47 by lbopp            ###   ########.fr       */
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
	if (tok_lst->type == LESS && tok_lst->next && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == LESSAND && tok_lst->next && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == GREAT && tok_lst->next && tok_lst->next->type == WORD)
		return (mv + 2);
	else if (tok_lst->type == GREATAND && tok_lst->next && tok_lst->next->type == WORD)
			return (mv + 2);
	else if (tok_lst->type == DGREAT && tok_lst->next && tok_lst->next->type == WORD)
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
	if ((tmp = isio_file(tok_lst, nb_tok, 0)))
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

int	iscmd_prefix(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	int	max;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	tmp = mv;
	if ((mv = isio_redirect(tok_lst, nb_tok, 0)) || (mv = is_word(tok_lst, 0)))
	{
		max = mv;
		while ((mv = isio_redirect(tok_lst, nb_tok, max)) || (mv = is_word(tok_lst, max)))
			max = mv;
	}
	return (max);
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
	tmp = mv;
	if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)) && (mv = is_word(tok_lst, mv)) &&
			(mv = iscmd_prefix(tok_lst, nb_tok, mv)))
	{
		return (tmp + mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)) && (mv = is_word(tok_lst, mv)))
	{
		return (tmp + mv);
	}
	else if (tok_lst->type == WORD && (mv = iscmd_prefix(tok_lst, nb_tok, 1)))
	{
		return (tmp + mv + 1);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
		return (tmp + mv);
	}
	else if (tok_lst->type == WORD)
	{
		return (tmp + 1);
	}
	return (0);
}

int	ispipe(t_token *tok_lst, int mv)
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
	if (tok_lst->type == PIPE)
		return (mv + 1);
	else
		return (0);
}

int	isnewline(t_token *tok_lst, int mv)
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
	if (tok_lst->type == NEWLINE)
		return (mv + 1);
	else
		return (0);
}

int	ispipe_sequence(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	int	max;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	tmp = mv;
	if ((mv = is_simplecmd(tok_lst, nb_tok, 0)))
	{
		max = mv;
		while ((mv = ispipe(tok_lst, max)) && (tmp = mv) &&
				(((mv = isnewline(tok_lst, tmp)) && (mv = is_simplecmd(tok_lst, nb_tok, mv))) || (mv = is_simplecmd(tok_lst, nb_tok, tmp))))
			max = mv;
	}
	return (max);
}

int	isand_or(t_token *tok_lst, int nb_tok, int mv)
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
	if ((mv = ispipe_sequence(tok_lst, nb_tok, 0)))
		return (tmp + mv);
	return (0);
}

int	isseparator_op(t_token *tok_lst, int mv)
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
	if (tok_lst->type == SEMICOLON)
		return (mv + 1);
	else
		return (0);
}

int	islist(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	int	max;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	if ((mv = isand_or(tok_lst, nb_tok, mv)))
	{
		max = mv;
		while ((mv = isseparator_op(tok_lst, mv)) && (mv = isand_or(tok_lst, nb_tok, mv)))
			max = mv;
	}
	return (max);
}

int	iscomplete_cmd(t_token *tok_lst, int nb_tok, int mv)
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
	if ((mv = islist(tok_lst, nb_tok, 0)))
		return (mv);
	return (0);
}
