/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:34:23 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 17:03:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Function used to get the last state of our lexer
*/

t_state	*get_last_state(t_state *state_lst)
{
	t_state	*last;

	last = NULL;
	while (state_lst)
	{
		last = state_lst;
		state_lst = state_lst->next;
	}
	return (last);
}
