/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/30 16:09:05 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

#define READ_END 0
#define WRITE_END 1

/*void	run_pipe(t_ast_node *ast_tree)
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
		g_test_fd = pdes[READ_END];
		printf("HERE TEST_FD = %d\n", g_test_fd);
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
	{
		wait(NULL);
		printf("TEST_FD = %d\n", g_test_fd);
	}
}*/

static void print_my_ast(t_ast_node *ast_tree, int mode, int layer)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		print_my_ast(ast_tree->left, 1, layer + 1);
	if (ast_tree->right)
		print_my_ast(ast_tree->right, 2, layer + 1);
	if (mode == 0)
		printf("ROOT = [%s] layer = %d\n", ast_tree->content, layer);
	if (mode == 1)
		printf("LEFT = [%s] layer = %d\n", ast_tree->content, layer);
	if (mode == 2)
		printf("RIGHT = [%s] layer = %d\n", ast_tree->content, layer);
}

int		main_exec(t_ast_node *ast_tree);

void	run_pipe(t_ast_node *ast_tree)
{
	pid_t	child;
	int		p[2];
	char	**cmd;
	char	*tmp;

	cmd = NULL;
	pipe(p);
	child = fork();
	//printf("On run_pipe pour [%s] et [%s]\n", ast_tree->left->content, ast_tree->right->content);
	if (child == 0)
	{
		dup2(p[WRITE_END], STDOUT_FILENO);
		close(p[READ_END]);
		main_exec(ast_tree->left);
	}
	if (child > 0)
	{
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		cmd = ft_strsplit(ast_tree->right->content, ' ');
		tmp = ft_strdup(cmd[0]);
		free(cmd[0]);
		if (!ft_strcmp(cmd[0], "wc") || !ft_strcmp(cmd[0], "sort"))
			cmd[0] = ft_strjoin("/usr/bin/", tmp);
		else
			cmd[0] = ft_strjoin("/bin/", tmp);
		//printf("On va executer la cmd [%s]\n", cmd[0]);
		execve(cmd[0], cmd, NULL);
	}
}

int		main_exec(t_ast_node *ast_tree)
{
	char	**cmd;
	char	*tmp;

	//printf("ICI on a [%s]\n", ast_tree->content);
	if (ast_tree->type == PIPE)
	{
		run_pipe(ast_tree);
	}
	else
	{
		cmd = ft_strsplit(ast_tree->content, ' ');
		tmp = ft_strdup(cmd[0]);
		free(cmd[0]);
		if (!ft_strcmp(cmd[0], "wc") || !ft_strcmp(cmd[0], "sort"))
			cmd[0] = ft_strjoin("/usr/bin", tmp);
		else
			cmd[0] = ft_strjoin("/bin/", tmp);
		execve(cmd[0], cmd, NULL);
	}
	return (0);
}

int		execution(t_ast_node *ast_tree, char **env)
{
	pid_t	child;

	(void)env;
	child = fork();
	if (child == 0)
	{
		main_exec(ast_tree);
		return (0);
	}
	if (child > 0)
		wait(NULL);
	//print_my_ast(ast_tree, 0, 0);
	return (0);
}
