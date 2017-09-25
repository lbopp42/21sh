/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tok_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 10:30:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/25 12:13:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	free_tok_lst(t_token **tok_lst)
{
	t_token	*last;

	while (*tok_lst)
	{
		last = *tok_lst;
		ft_strdel(&(*tok_lst)->content);
		*tok_lst = (*tok_lst)->next;
		free(last);
	}
}
