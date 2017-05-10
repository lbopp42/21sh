/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_piece_of_bigop.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 09:21:07 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/10 09:21:13 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	is_piece_of_bigop(t_token **tok_lst, t_state **st_lst, int *sp, int i)
{
	int	tmp;

	tmp = 0;
	if (!*sp && *tok_lst && (*tok_lst)->type >= SEMICOLON &&
			(*tok_lst)->type <= LESSAND &&
			(tmp = big_op((*tok_lst)->content, i)) != WORD && !*st_lst)
	{
		*sp = 0;
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
		*sp = 0;
	}
	else
		return (0);
	return (1);
}
