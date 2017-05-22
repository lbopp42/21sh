/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/20 11:32:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	exec_pipe(char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	**ls;
	char	**cat;

	ls = (char**)ft_memalloc(sizeof(char*) * 2);
	ls[1] = ft_strdup("ls");
	ls[2] = ft_strdup("-a");
	cat = (char**)ft_memalloc(sizeof(char*) * 2);
	cat[1] = ft_strdup("cat");
	cat[2] = ft_strdup("-e");
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execve(ls[1], ls + 1, env);
		return ;
	}
	else
	{
		close(pipe_fd[1]);
		execve(cat[1], cat, env);
	}
	return ;
}

static void print_my_ast(t_ast_node *ast_tree, int mode, int layer)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		print_my_ast(ast_tree->left, 1, layer + 1);
	if (ast_tree->right)
		print_my_ast(ast_tree->right, 2, layer + 1);
	if (mode == 1)
		printf("LEFT = [%s]\n", ast_tree->content);
	else if (mode == 2)
		printf("RIGHT = [%s]\n", ast_tree->content);
	else
		printf("ROOT = [%s]\n", ast_tree->content);
}

void	execution(t_ast_node *ast_tree, char **env)
{
	print_my_ast(ast_tree, 0, 0);
	exec_pipe(env);
}
