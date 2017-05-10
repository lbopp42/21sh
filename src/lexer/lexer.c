/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 10:07:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/10 10:09:55 by lbopp            ###   ########.fr       */
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
	else if ((tmp = is_piece_of_bigop(tok_lst, st_lst, &sp, i)))
		return (tmp);
	else if (g_line[i] == '"' || g_line[i] == '\'')
		return (treatment_of_quote(tok_lst, st_lst, &sp, i));
	else if ((tmp = is_new_op(i)) != WORD && !*st_lst)
		return (treatment_new_op(tok_lst, &sp, i, tmp));
	else if (g_line[i] == '\n' && !*st_lst)
		return (treatment_newline(tok_lst, i, tmp));
	else if (!*st_lst && (g_line[i] == ' ' || g_line[i] == '\t'))
		sp = 1;
	else if (*tok_lst && (*tok_lst)->type == WORD && !sp)
		return (treatment_of_old_word(tok_lst, &sp, i));
	else
		return (treatment_of_new_word(tok_lst, &sp, i));
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
