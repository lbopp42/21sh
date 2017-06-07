/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_of_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 09:27:30 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/05 10:54:34 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	treatment_of_quote(t_token **tok_lst, t_state **st_lst, int *sp, int i)
{
	state_management(st_lst, g_line[i]);
	if (*tok_lst && !*sp && (*tok_lst)->type == WORD)
		add_to_current_tok(tok_lst, i, WORD);
	else if (*tok_lst)
	{
		*sp = 0;
		create_new_token_next(tok_lst, i, WORD);
		return (2);
	}
	else
		create_new_token(tok_lst, i, WORD);
	return (1);
}
