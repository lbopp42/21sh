/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:10:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/27 13:46:24 by lbopp            ###   ########.fr       */
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
	tmp = mv;
	if (nb_tok - mv >= 4 * i - (i - 1) && (mv = iscmd_prefix(tok_lst, nb_tok, 0, 2)) &&
			tok_lst->next && (mv = isio_redirect(tok_lst, nb_tok, mv)))
	{
		return (mv);
	}
	else if ((mv = isio_redirect(tok_lst, nb_tok, 0)))
	{
		return (mv);
	}
	else if (nb_tok - mv >= 4 * i - (i - 1) && (mv = iscmd_prefix(tok_lst, nb_tok, 0, 2)) &&
			(mv = is_word(tok_lst, mv)))
		return (mv);
	else if (tok_lst->type == WORD)
		return (tmp + 1);
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
	tmp = mv;
	if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)) && (mv = is_word(tok_lst, mv)) &&
			(mv = iscmd_prefix(tok_lst, nb_tok, mv, 1)))
	{
		return (tmp + mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)) && (mv = is_word(tok_lst, mv)))
	{
		return (tmp + mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0, 1)))
	{
		return (tmp + mv);
	}
	else if (tok_lst->type == WORD && (mv = iscmd_prefix(tok_lst, nb_tok, 1, 1)))
	{
		return (tmp + mv + 1);
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

int	ispipe_sequence(t_token *tok_lst, int nb_tok, int mv, int mode)
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
	if (nb_tok - mv >= 3 * i - (i - 1) && (mv = ispipe_sequence(tok_lst, nb_tok, 0, 2)) &&
			(mv = ispipe(tok_lst, mv)) && (((tmp = isnewline(tok_lst, mv)) &&
				(mv = is_simplecmd(tok_lst, nb_tok, tmp))) ||
				(mv = is_simplecmd(tok_lst, nb_tok, mv))))
	{
		return (mv);
	}
	else if ((mv = is_simplecmd(tok_lst, nb_tok, 0)))
	{
		return (mv);
	}
	return (0);
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
	if ((mv = ispipe_sequence(tok_lst, nb_tok, 0, 1)))
		return (mv);
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

int	islist(t_token *tok_lst, int nb_tok, int mv, int mode)
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
	if (nb_tok - mv >= 3 * i - (i - 1) && (mv = islist(tok_lst, nb_tok, 0, 2)) &&
			(mv = isseparator_op(tok_lst, mv)) && (mv = isand_or(tok_lst, nb_tok, mv)))
		return (mv);
	else if ((mv = isand_or(tok_lst, nb_tok, mv)))
		return (mv);
	return (0);
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
	if (nb_tok >= 2 && (mv = islist(tok_lst, nb_tok, 0, 1)) &&
			(mv = isseparator_op(tok_lst, mv)))
		return (mv);
	else if ((mv = islist(tok_lst, nb_tok, 0, 1)))
		return (mv);
	return (0);
}
