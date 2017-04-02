/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:27:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 16:29:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

t_token	*get_last_token(t_token *tok_lst)
{
	t_token	*last;

	last = tok_lst;
	while (last->next)
		last = last->next;
	return (last);
}
