/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/28 10:08:03 by lbopp            ###   ########.fr       */
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
	get_token(&tok_lst, &state_lst);
	print_lst(tok_lst);
	return (1);
}
