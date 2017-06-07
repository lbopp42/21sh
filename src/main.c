/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/07 15:15:10 by lbopp            ###   ########.fr       */
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

void	free_ast_tree(t_ast_node **ast_tree)
{
	if (!*ast_tree)
		return ;
	else if ((*ast_tree)->left)
		free_ast_tree(&(*ast_tree)->left);
	else if ((*ast_tree)->right)
		free_ast_tree(&(*ast_tree)->right);
	free((*ast_tree)->content);
	(*ast_tree)->content = NULL;
	free(*ast_tree);
	*ast_tree = NULL;
}

int		main(int ac, char **av, char **env)
{
	t_token	*tok_lst;
	t_state	*state_lst;
	t_tuple	*tuple_parse;
	int		nb_tok;

	(void)ac;
	g_env = env;
	(void)av;
	while (1)
	{
		ft_putstr("$> ");
		g_line = NULL;
		tuple_parse = NULL;
		state_lst = NULL;
		tok_lst = NULL;
		get_next_line(0, &g_line);
		nb_tok = lexer_posix(&tok_lst, &state_lst);
		free(g_line);
		if (state_lst)
		{
			free_state_lst(&state_lst);
			ft_putendl("Lexical problem !");
			exit(EXIT_FAILURE);
		}
		if (g_line && g_line[0])
			tuple_parse = iscomplete_cmd(tok_lst, 0, 0);
		else
			exit(0);
		free_tok_lst(&tok_lst);
		if (nb_tok != tuple_parse->mv)
		{
			ft_putendl("Syntax error !\n");
			exit(EXIT_FAILURE);
		}
		main_expand(&tuple_parse->ast_tree);
		execution(tuple_parse->ast_tree, env);
		free_ast_tree(&tuple_parse->ast_tree);
		free(tuple_parse);
	}
	return (1);
}
