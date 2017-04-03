/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:42:38 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/03 15:04:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	print_lst(t_token *tok_lst)
{
	t_token	*tmp;
	const char	*test[] = {"SEMICOLON", "PIPE", "LESS", "DLESS", "GREAT", "DGREAT",
		"INPUT", "OUTPUT", "QUOTE", "DQUOTE", "BQUOTE", "WORD"};

	tmp = tok_lst;
	while (tmp)
	{
		printf("TOKEN = [%s] and TYPE = %s\n", tmp->content, test[tmp->type]);
		tmp = tmp->next;
	}
}

void	print_state_lst(t_state *state_lst)
{
	t_state	*tmp;

	tmp = state_lst;
	while (tmp)
	{
		printf("In state_list : %d\n", tmp->state);
		tmp = tmp->next;
	}
}
