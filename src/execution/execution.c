/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/24 16:42:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

#define READ_END 0
#define WRITE_END 1

void	run_pipe(t_ast_node *ast_tree)
{
	pid_t	child = -1;
	char	**cmd1;
	char	*tmp;
	char	**cmd2;
	int		pdes[2];

	cmd1 = ft_strsplitquote(ast_tree->left->content, ' ');
	cmd2 = ft_strsplitquote(ast_tree->right->content, ' ');
	tmp = ft_strdup(cmd1[0]);
	free(cmd1[0]);
	cmd1[0] = ft_strdup("/bin/");
	cmd1[0] = ft_stradd(cmd1[0], tmp);
	free(tmp);
	tmp = ft_strdup(cmd2[0]);
	free(cmd2[0]);
	cmd2[0] = ft_strdup("/bin/");
	cmd2[0] = ft_stradd(cmd2[0], tmp);
	free(tmp);
	pipe(pdes);
	child = fork();
	if (child == 0)
	{
		dup2(pdes[WRITE_END], STDOUT_FILENO);
		close(pdes[READ_END]);
		execve(cmd1[0], cmd1, NULL);
	}
	if (child > 0)
	{
		dup2(pdes[READ_END], STDIN_FILENO);
		close(pdes[WRITE_END]);
		wait(NULL);
		execve(cmd2[0], cmd2, NULL);
		return ;
	}
}

void	exec_pipe(t_ast_node *ast_tree)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		run_pipe(ast_tree);
		return ;
	}
	if (child > 0)
		wait(NULL);
}

static void print_my_ast(t_ast_node *ast_tree)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		print_my_ast(ast_tree->left);
	if (ast_tree->right)
		print_my_ast(ast_tree->right);
	if (ast_tree->type == PIPE)
		exec_pipe(ast_tree);
}

void	execution(t_ast_node *ast_tree, char **env)
{
	(void)env;
	print_my_ast(ast_tree);
}
