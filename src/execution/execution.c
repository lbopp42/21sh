/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/03 12:37:42 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <fcntl.h>

#define READ_END 0
#define WRITE_END 1
#define ERROR_NO_FILE 1

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
	int		tmp_out;
	static	int	first = 0;

	new_fd = open(ast_tree->right->content, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	tmp_out = dup(1);
	if (first == 0)
	{
		dup2(new_fd, 1);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left, in_fork);
	close(1);
	dup2(tmp_out, 1);
	first = 0;
}

void	run_redir_dgreat(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	static	int	first = 0;
	int		tmp_out;

	new_fd = open(ast_tree->right->content, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	tmp_out = dup(1);
	if (first == 0)
	{
		dup2(new_fd, 1);
		first = 1;
	}
	close(new_fd);
	main_exec(ast_tree->left, in_fork);
	close(1);
	first = 0;
	dup2(tmp_out, 1);
}

void	run_redir_less(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	static	int	first = 0;
	int		tmp_in;

	new_fd = open(ast_tree->right->content, O_RDONLY, S_IRUSR | S_IWUSR);
	tmp_in = dup(0);
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
	main_exec(ast_tree->left, in_fork);
	close(0);
	dup2(tmp_in, 0);
	first = 0;
}

void	run_semicolon(t_ast_node *ast_tree)
{
	main_exec(ast_tree->left, 0);
	main_exec(ast_tree->right, 0);
}

void	run_redir_dless(t_ast_node *ast_tree, int in_fork)
{
	char		*line;
	pid_t		child;
	int			p[2];
	int			tmp_in;

	pipe(p);
	line = here_doc(NULL, 0);
	child = fork();
	if (child == 0)
	{
		dup2(p[WRITE_END], 1);
		close(READ_END);
		ft_putstr(line);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		{
			tmp_in = dup(ft_atoi(ast_tree->left->content));
			dup2(p[READ_END], ft_atoi(ast_tree->left->content));
			close(p[WRITE_END]);
			main_exec(ast_tree->left->left, in_fork);
		}
		else
		{
			tmp_in = dup(0);
			dup2(p[READ_END], 0);
			close(p[WRITE_END]);
			main_exec(ast_tree->left, in_fork);
		}
		if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
			dup2(tmp_in, ft_atoi(ast_tree->left->content));
		else
			dup2(tmp_in, 0);
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

void	run_greatand(t_ast_node *ast_tree, int in_fork)
{
	int	fd_move;
	int	fd_new;
	int	tmp_fd;

	fd_move = 1;
	printf("A DROITE = [%s]\n", ast_tree->right->content);
	printf("A GAUCHE = [%s]\n", ast_tree->left->content);
	if (ast_tree->left->type == IO_NUMBER)
		fd_move = ft_atoi(ast_tree->left->content);
	tmp_fd = dup(fd_move);
	if (ft_strequ(ast_tree->right->content, "-"))
	{
		printf("On ferme [%d]\n", fd_move);
		close(fd_move);
	}
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
	}
	if (ast_tree->left->type == IO_NUMBER)
	{
		printf("On lance la commande d'ici\n");
		main_exec(ast_tree->left->left, in_fork);
	}
	else
		main_exec(ast_tree->left->left, in_fork);
	dup2(tmp_fd, fd_move);
	printf("On reset [%d]\n", fd_move);
}

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
	else if (ast_tree->type == LESS)
		run_redir_less(ast_tree, in_fork);
	else if (ast_tree->type == SEMICOLON)
		run_semicolon(ast_tree);
	else if (ast_tree->type == DGREAT)
		run_redir_dgreat(ast_tree, in_fork);
	else if (ast_tree->type == DLESS)
		run_redir_dless(ast_tree, in_fork);
	else if (ast_tree->type == GREATAND)
		run_greatand(ast_tree, in_fork);
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
	print_my_ast(ast_tree, 0, 0);
	main_exec(ast_tree, 0);
	return (0);
}
