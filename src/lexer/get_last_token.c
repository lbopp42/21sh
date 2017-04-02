/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:27:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 17:03:49 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Function used to get the last token of our lexer
*/

t_token	*get_last_token(t_token *tok_lst)
{
	t_token	*last;

	last = tok_lst;
	while (last->next)
		last = last->next;
	return (last);
}
