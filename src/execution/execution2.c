/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/25 15:30:19 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define READ_END 0
#define WRITE_END 1

int		loop_pipe(char *command)
{
	int			fdes[2];
	char		**cmd;
	char		*tmp;
	pid_t		pid;
	static int	fd_in = 0;

	printf("On entre pour [%s]\n", command);
	if (command && (!ft_strncmp(command, "cat", 3) || !ft_strncmp(command, "ls", 2)))
	{
		cmd = ft_strsplitquote(command, ' ');
		tmp = ft_strdup(cmd[0]);
		cmd[0] = ft_strjoin("/bin/", tmp);
	}
	else if (command)
	{
		cmd = ft_strsplitquote(command, ' ');
		tmp = ft_strdup(cmd[0]);
		cmd[0] = ft_strjoin("/usr/bin/", tmp);
	}
	pipe(fdes);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2(fd_in, 0);
		if (command != NULL)
			dup2(fdes[WRITE_END], 1);
		close(fdes[READ_END]);
		printf("on exec [%s]\n", cmd[0]);
		execve(cmd[0], cmd, NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		close(fdes[WRITE_END]);
		if (command != NULL)
			fd_in = fdes[READ_END];
		else
			close(fdes[READ_END]);
		return (1);
	}
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
	{
		if (loop_pipe(ast_tree->left->content))
		{
			if (loo	p_pipe(ast_tree->right->content))
				loop_pipe(NULL);
		}
	}
}

void	execution(t_ast_node *ast_tree, char **env)
{
	(void)env;
	print_my_ast(ast_tree);
}
