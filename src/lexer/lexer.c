/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 10:07:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 13:59:52 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	treatment_char(t_token **tok_lst, t_state **st_lst, int i)
{
	int			tmp;
	static int	sp = 0;

	if (!g_line[i])
	{
		if (*tok_lst)
			(*tok_lst)->next = NULL;
		return (0);
	}
	else if (!sp && *tok_lst && (*tok_lst)->type >= SEMICOLON &&
			(*tok_lst)->type <= LESSAND &&
			(tmp = big_op((*tok_lst)->content, i)) != WORD && !*st_lst)
	{
		sp = 0;
		add_to_current_tok(tok_lst, i, tmp);
	}
	else if (*tok_lst && (*tok_lst)->type >= SEMICOLON &&
			(*tok_lst)->type <= LESSAND &&
			big_op((*tok_lst)->content, i) == WORD && !*st_lst)
	{
		if (g_line[i] != ' ' && g_line[i] != '\t')
		{
			create_new_token_next(tok_lst, i, is_new_op(i));
			return (2);
		}
		sp = 0;
	}
	else if (g_line[i] == '"' || g_line[i] == '\'')
	{
		state_management(st_lst, i);
		if (*tok_lst && !sp && (*tok_lst)->type == WORD)
			add_to_current_tok(tok_lst, i, WORD);
		else if (*tok_lst)
		{
			sp = 0;
			create_new_token_next(tok_lst, i, WORD);
			return (2);
		}
		else
			create_new_token(tok_lst, i, WORD);
	}
	else if ((tmp = is_new_op(i)) != WORD && !*st_lst)
	{
		sp = 0;
		if (*tok_lst)
		{
			if ((tmp == GREAT || tmp == LESS) && is_digit_token((*tok_lst)->content))
				(*tok_lst)->type = IO_NUMBER;
			create_new_token_next(tok_lst, i, tmp);
			return (2);
		}
		else
			create_new_token(tok_lst, i, tmp);
	}
	else if (g_line[i] == '\n' && !*st_lst)
	{
		if (*tok_lst)
		{
			create_new_token_next(tok_lst, i, NEWLINE);
			return (2);
		}
		else
			create_new_token(tok_lst, i, tmp);
	}
	else if (!*st_lst && (g_line[i] == ' ' || g_line[i] == '\t'))
		sp = 1;
	else if (*tok_lst && (*tok_lst)->type == WORD && !sp)
	{
		sp = 0;
		add_to_current_tok(tok_lst, i, WORD);
	}
	else
	{
		if (sp && *tok_lst)
		{
			sp = 0;
			create_new_token_next(tok_lst, i, WORD);
			return (2);
		}
		else
		{
			sp = 0;
			create_new_token(tok_lst, i, WORD);
		}
	}
	return (1);
}

int	treatment_cursor(t_token **tok_lst, int *i, int *nb_tok, int tmp)
{
	if (tmp == 1)
		*i += 1;
	else if (tmp == 2)
	{
		*nb_tok += 1;
		*tok_lst = (*tok_lst)->next;
		*i += 1;
	}
	else
		return (0);
	return (1);
}

/*
**	"test = 0;" is only usefull when we run test
*/

int	lexer_posix(t_token **tok_lst, t_state **st_lst)
{
	int			i;
	int			nb_tok;
	static int	test = 0;
	int			tmp;
	t_token		*first;

	i = 0;
	test = 0;
	nb_tok = 0;
	first = NULL;
	while ((tmp = treatment_char(tok_lst, st_lst, i)))
	{
		if (*tok_lst && !test)
		{
			nb_tok += 1;
			first = *tok_lst;
			test += 1;
		}
		if (!treatment_cursor(tok_lst, &i, &nb_tok, tmp))
			break ;
	}
	*tok_lst = first;
	return (nb_tok);
}
