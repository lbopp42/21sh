/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/02 12:13:26 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1
#define ERROR_NO_FILE 1

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

int		main_exec(t_ast_node *ast_tree, int in_fork);
//void	exec_cmd(char *content, int in, int out);

void	run_pipe(t_ast_node *ast_tree)
{
	pid_t	child;
	int		p[2];

	pipe(p);
	child = fork();
	if (child == 0)
	{
		dup2(p[WRITE_END], STDOUT_FILENO);
		close(p[READ_END]);
		close(p[WRITE_END]);
		main_exec(ast_tree->left, 1);
	}
	if (child > 0)
		wait(NULL);
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		close(p[READ_END]);
		main_exec(ast_tree->right, 1);
}

void	run_redir_great(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	int		tmp_in;
	static	int	first = 0;

	new_fd = open(ast_tree->right->content, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	tmp_in = dup(1);
	if (first == 0)
	{
		dup2(new_fd, 1);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left, in_fork);
	close(1);
	dup2(tmp_in, 1);
	first = 0;
}

/*void	run_redir_dgreat(t_ast_node *ast_tree)
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

*/void	run_semicolon(t_ast_node *ast_tree)
{
	main_exec(ast_tree->left, 0);
	main_exec(ast_tree->right, 0);
}/*

void	run_redir_dless(t_ast_node *ast_tree)
{
	pid_t	child;
	pid_t	child2;
	int		p[2];
	char	*line;

	line = NULL;
	pipe(p);
	child = fork();
	child2 = fork();
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
		if (child2 == 0)
		{
			ft_strdel(&line);
			dup2(p[READ_END], STDIN_FILENO);
			close(p[WRITE_END]);
			main_exec(ast_tree->left);
		}
		if (child2 > 0)
			wait(NULL);
	}
}

int		ft_isnumber(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] - '0' < 0 && content[i] - '0' > 9)
			return (0);
		i += 1;
	}
	return (1);
}

void	run_greatand(t_ast_node *ast_tree)
{
	int	fd_move;
	int	fd_new;

	fd_move = 1;
	if (ast_tree->left->type == IO_NUMBER)
		fd_move = ft_atoi(ast_tree->left->content);
	if (ft_strequ(ast_tree->right->content, "-"))
		close(fd_move);
	else
	{
		if (ft_isnumber(ast_tree->right->content) && (fd_new = dup(ft_atoi(ast_tree->right->content))) == -1) //TODO
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content, 2);
			ft_putendl_fd(": Bad file descriptor", 2);
			exit(1);
		}
		else if (!ft_isnumber(ast_tree->right->content))
			fd_new = open(ast_tree->right->content, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd_move, fd_new);
		close(fd_move);
		if (ast_tree->left->type == IO_NUMBER)
			main_exec(ast_tree->left->left);
		else
			main_exec(ast_tree->left);
	}
}*/

/*
**	If the command isn't a builtin we exec_cmd().
*/

/*void	exec_cmd(char *content, int in, int out)
{
	pid_t	child;
	int		p[2];

	pipe(p);
	child = fork();
	if (child == 0)
	{
		dup2(p[WRITE_END], out);
		close(p[WRITE_END]);
		close(p[READ_END]);
	}
	if (child > 0)
	{
		wait(NULL);
		dup2(p[READ_END], in);
		close(p[READ_END]);
		close(p[WRITE_END]);
	}
}*/

void	launch_pipe(t_ast_node *ast_tree)
{
	pid_t		child;
	static int	fork_nb = 0;

	if (fork_nb == 0)
	{
		fork_nb = 1;
		child = fork();
		if (child == 0)
		{
			run_pipe(ast_tree);
		}
		if (child > 0)
		{
			wait(NULL);
			fork_nb = 0;
		}
	}
	else
		run_pipe(ast_tree);
}

int		main_exec(t_ast_node *ast_tree, int in_fork)
{
	char	**cmd;
	char	*tmp;
	pid_t	child;

	//Faire un tableau de pointeur sur fonction ou autre + leaks.
	if (ast_tree->type == PIPE)
		launch_pipe(ast_tree);
	else if (ast_tree->type == GREAT)
		run_redir_great(ast_tree, in_fork);
	/*else if (ast_tree->type == LESS)
		run_redir_less(ast_tree);*/
	else if (ast_tree->type == SEMICOLON)
		run_semicolon(ast_tree);
	/*else if (ast_tree->type == DGREAT)
		run_redir_dgreat(ast_tree);
	else if (ast_tree->type == DLESS)
		run_redir_dless(ast_tree);
	else if (ast_tree->type == GREATAND)
		run_greatand(ast_tree);*/
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
		if (in_fork)
			execve(cmd[0], cmd, NULL);
		else
		{
			child = fork();
			if (child == 0)
				execve(cmd[0], cmd, NULL);
			else
				wait(NULL);
		}
	}
	return (0);
}

int		execution(t_ast_node *ast_tree, char **env)
{
	(void)env;
	main_exec(ast_tree, 0);
	//print_my_ast(ast_tree, 0, 0);
	return (0);
}
