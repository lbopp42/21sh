/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:26:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/19 13:43:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	init_term(void)
{
	char			*term;
	struct termios	attr;

	tcgetattr(0, &g_origin_term);
	tcgetattr(0, &attr);
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attr);
	if (!(term = getenv("TERM")) || tgetent(NULL, term) == -1)
	{
		ft_putendl_fd("lsh: environment not found", 2);
		default_term();
		exit(0);
	}
}

void	default_term(void)
{
	tcsetattr(0, TCSADRAIN, &g_origin_term);
	tgetent(NULL, getenv("TERM"));
}

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
	t_token			*tok_lst;
	t_state			*state_lst;
	t_tuple			*tuple_parse;
	int				nb_tok;

	(void)ac;
	g_last_status = 0;
	g_env = env;
	(void)av;
	main_history();
	while (1)
	{
		g_line = NULL;
		tuple_parse = NULL;
		state_lst = NULL;
		tok_lst = NULL;
		g_line = editing_line("Hello > ");
		if (!g_line || !g_line[0])
			continue ;
		nb_tok = lexer_posix(&tok_lst, &state_lst);
		while (state_lst)
		{
			g_line = ft_stradd(g_line, editing_line("> "));
			merge_history(&g_history->prev, &g_history);
			g_history = g_history->prev;
			tok_lst = NULL; //Need to be remove properly
			state_lst = NULL;
			nb_tok = lexer_posix(&tok_lst, &state_lst);
			continue ;
		}
		if (g_line && g_line[0])
			tuple_parse = iscomplete_cmd(tok_lst, 0, 0);
		else
		{
			ft_strdel(&g_line);
			continue ;
		}
		free_tok_lst(&tok_lst);
		if (nb_tok != tuple_parse->mv)
		{
			ft_putendl("Syntax error !");
			ft_strdel(&g_line);
			continue ;
		}
		ft_strdel(&g_line);
		main_expand(&tuple_parse->ast_tree);
		execution(tuple_parse->ast_tree, env);
		free_ast_tree(&tuple_parse->ast_tree);
		free(tuple_parse);
	}
	return (0);
}
