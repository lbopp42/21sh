/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/01 10:54:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1
#define ERROR_NO_FILE 1

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

/*static void print_my_ast(t_ast_node *ast_tree, int mode, int layer)
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
}*/

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
	if (child == 0)
	{
		dup2(p[WRITE_END], STDOUT_FILENO);
		close(p[READ_END]);
		main_exec(ast_tree->left);
	}
	if (child > 0)
	{
		wait(NULL);
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		cmd = ft_strsplit(ast_tree->right->content, ' ');
		tmp = ft_strdup(cmd[0]);
		free(cmd[0]);
		if (!ft_strcmp(cmd[0], "wc") || !ft_strcmp(cmd[0], "sort"))
			cmd[0] = ft_strjoin("/usr/bin/", tmp);
		else
			cmd[0] = ft_strjoin("/bin/", tmp);
		execve(cmd[0], cmd, NULL);
	}
}

void	run_redir_great(t_ast_node *ast_tree)
{
	int		new_fd;
	static	int	first = 0;

	new_fd = open(ast_tree->right->content, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (first == 0)
	{
		dup2(new_fd, 1);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left);
	first = 0;
}

void	run_redir_dgreat(t_ast_node *ast_tree)
{
	int		new_fd;
	static	int	first = 0;

	new_fd = open(ast_tree->right->content, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (first == 0)
	{
		dup2(new_fd, 1);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left);
}

void	run_redir_less(t_ast_node *ast_tree)
{
	int		new_fd;
	static	int	first = 0;

	new_fd = open(ast_tree->right->content, O_RDONLY, S_IRUSR | S_IWUSR);
	if (new_fd == -1)
	{
		ft_putstr_fd("lsh: ", 2);
		ft_putstr_fd(ast_tree->right->content, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (first == 0)
	{
		dup2(new_fd, 0);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left);
}

void	run_semicolon(t_ast_node *ast_tree)
{
	pid_t	child;

	child = fork();
	if (child == 0)
		main_exec(ast_tree->left);
	if (child > 0)
	{
		wait(NULL);
		main_exec(ast_tree->right);
	}
}

void	run_redir_dless(t_ast_node *ast_tree)
{
	pid_t	child;
	int		p[2];
	char	*line;

	line = NULL;
	pipe(p);
	child = fork();
	if (child == 0)
	{
		dup2(p[WRITE_END], STDOUT_FILENO);
		close(p[READ_END]);
		while (get_next_line(0, &line))
		{
			if (ft_strequ(line, ast_tree->right->content))
				break ;
			ft_putendl(line);
		}
		exit(0);
	}
	if (child > 0)
	{
		wait(NULL);
		ft_strdel(&line);
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		main_exec(ast_tree->left);
	}
}

int		main_exec(t_ast_node *ast_tree)
{
	char	**cmd;
	char	*tmp;

	//Faire un tableau de pointeur sur fonction ou autre + leaks.
	if (ast_tree->type == PIPE)
		run_pipe(ast_tree);
	else if (ast_tree->type == GREAT)
		run_redir_great(ast_tree);
	else if (ast_tree->type == LESS)
		run_redir_less(ast_tree);
	else if (ast_tree->type == SEMICOLON)
		run_semicolon(ast_tree);
	else if (ast_tree->type == DGREAT)
		run_redir_dgreat(ast_tree);
	else if (ast_tree->type == DLESS)
		run_redir_dless(ast_tree);
	else
	{
		cmd = ft_strsplit(ast_tree->content, ' ');
		tmp = ft_strdup(cmd[0]);
		if (!ft_strcmp(cmd[0], "wc") || !ft_strcmp(cmd[0], "sort"))
		{	
			free(cmd[0]);
			cmd[0] = ft_strjoin("/usr/bin/", tmp);
		}
		else
		{
			free(cmd[0]);
			cmd[0] = ft_strjoin("/bin/", tmp);
		}
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
