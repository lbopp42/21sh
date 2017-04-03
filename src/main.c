/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/03 10:00:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	free_tok_lst(t_token **tok_lst)
{
	if (!*tok_lst)
		return ;
	if ((*tok_lst)->next)
		free_tok_lst(&(*tok_lst)->next);
	free((*tok_lst)->content);
	free(*tok_lst);
}

void	free_state_lst(t_state **state_lst)
{
	if (!*state_lst)
		return ;
	if ((*state_lst)->next)
		free_state_lst(&(*state_lst)->next);
	free(*state_lst);
}

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
		free_state_lst(&state_lst);
		ft_putendl("Lexical problem !");
	}
	print_lst(tok_lst);
	free_tok_lst(&tok_lst);
	return (1);
}
