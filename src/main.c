/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 14:39:14 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		main(void)
{
	t_token	*tok_lst;
	t_state	*state_lst;

	g_line = NULL;
	state_lst = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	fill_tok_lst(&tok_lst, &state_lst);
	if (state_lst)
	{
		ft_putendl("Lexical problem !");
		while (state_lst)
		{
			printf("State = %d\n", state_lst->state);
			state_lst = state_lst->next;
		}
	}
	print_lst(tok_lst);
	return (1);
}
