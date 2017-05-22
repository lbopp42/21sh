/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/20 11:32:47 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*void	free_tok_lst(t_token **tok_lst)
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
}*/

int		main(int ac, char **av, char **env)
{
	t_token	*tok_lst;
	t_state	*state_lst;
	t_tuple	*tuple_parse;
	int		nb_tok;

	(void)ac;
	(void)av;
	g_line = NULL;
	state_lst = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	nb_tok = lexer_posix(&tok_lst, &state_lst);
	if (state_lst)
	{
		//free_state_lst(&state_lst);
		ft_putendl("Lexical problem !");
		exit(EXIT_FAILURE);
	}
	tuple_parse = iscomplete_cmd(tok_lst, 0, 0);
	if (nb_tok != tuple_parse->mv)
	{
		ft_putendl("Syntax error !\n");
		exit(EXIT_FAILURE);
	}
	execution(tuple_parse->ast_tree, env);
	return (1);
}
