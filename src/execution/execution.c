/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/12 14:59:20 by lbopp            ###   ########.fr       */
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

int		main_exec(t_ast_node *ast_tree, int in_fork, int fd_min);
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
		main_exec(ast_tree->left, 1, 10);
	}
	if (child > 0)
		wait(NULL);
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		close(p[READ_END]);
		main_exec(ast_tree->right, 1, 10);
}

void	run_redir_great(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	int		tmp_out;
	static	int	first = 0;
	int		fd_default;

	fd_default = 1;
	new_fd = open(ast_tree->right->content->content,
			O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	tmp_out = dup(fd_default);
	if (first == 0)
	{
		dup2(new_fd, fd_default);
		first = 1;
	}
	close(new_fd);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER && ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, 10);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, 10);
	close(fd_default);
	dup2(tmp_out, fd_default);
	first = 0;
}

void	run_redir_dgreat(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	static	int	first = 0;
	int		tmp_out;
	int		fd_default;

	fd_default = 1;
	new_fd = open(ast_tree->right->content->content,
			O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	tmp_out = dup(fd_default);
	if (first == 0)
	{
		dup2(new_fd, fd_default);
		first = 1;
	}
	close(new_fd);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER && ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, 10);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, 10);
	close(fd_default);
	first = 0;
	dup2(tmp_out, fd_default);
}

void	run_redir_less(t_ast_node *ast_tree, int in_fork)
{
	int		new_fd;
	static	int	first = 0;
	int		tmp_in;
	int		fd_default;

	fd_default = 0;
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	new_fd = open(ast_tree->right->content->content, O_RDONLY, S_IRUSR | S_IWUSR);
	tmp_in = dup(fd_default);
	if (new_fd == -1)
	{
		ft_putstr_fd("lsh: ", 2);
		ft_putstr_fd(ast_tree->right->content->content, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (in_fork)
			exit(1);
		else
			return ;
	}
	if (first == 0)
	{
		dup2(new_fd, fd_default);
		first = 1;
	}
	close(new_fd);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER && ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, 10);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, 10);
	close(fd_default);
	dup2(tmp_in, fd_default);
	first = 0;
}

void	run_semicolon(t_ast_node *ast_tree)
{
	main_exec(ast_tree->left, 0, 10);
	main_exec(ast_tree->right, 0, 10);
}

void	run_redir_dless(t_ast_node *ast_tree, int in_fork)
{
	t_list		*list;
	pid_t		child;
	int			p[2];
	int			tmp_in;

	pipe(p);
	list = here_doc(NULL, 0);
	launch_expand(&list);
	child = fork();
	if (child == 0)
	{
		dup2(p[WRITE_END], 1);
		close(READ_END);
		while (list)
		{
			ft_putstr(list->content);
			list = list->next;
		}
		exit(0);
	}
	else
	{
		wait(NULL);
		if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		{
			tmp_in = dup(ft_atoi(ast_tree->left->content->content));
			dup2(p[READ_END], ft_atoi(ast_tree->left->content->content));
			close(p[WRITE_END]);
			main_exec(ast_tree->left->left, in_fork, 10);
		}
		else
		{
			tmp_in = dup(0);
			dup2(p[READ_END], 0);
			close(p[WRITE_END]);
			main_exec(ast_tree->left, in_fork, 10);
		}
		if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
			dup2(tmp_in, ft_atoi(ast_tree->left->content->content));
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
		if (content[i] < '0' || content[i] > '9')
			return (0);
		i += 1;
	}
	return (1);
}

void	run_greatand(t_ast_node *ast_tree, int in_fork, int fd_min)
{
	int	fd_new;
	int	fd_default;

	fd_default = 1;
	fd_new = -1;
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	dup2(fd_default, fd_min);
	if (ft_strequ(ast_tree->right->content->content, "-"))
		close(fd_default);
	else
	{
		if (ft_isnumber(ast_tree->right->content->content) &&
				ft_atoi(ast_tree->right->content->content) > 9)
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content->content, 2);
			ft_putendl_fd(": illegal file descriptor name", 2);
			if (in_fork)
				exit(1);
			else
				return ;
		}
		else if (ft_isnumber(ast_tree->right->content->content)
				&& (fd_new = dup(ft_atoi(ast_tree->right->content->content))) == -1)
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content->content, 2);
			ft_putendl_fd(": Bad file descriptor", 2);
			if (in_fork)
				exit(1);
			else
				return ;
		}
		else if (!ft_isnumber(ast_tree->right->content->content))
			fd_new = open(ast_tree->right->content->content,
					O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd_default, fd_new);
		close(fd_default);
	}
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER && ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, fd_min + 1);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, fd_min + 1);
	dup2(fd_min, fd_default);
	close(fd_new);
}

void	run_lessand(t_ast_node *ast_tree, int in_fork, int fd_min)
{
	int	fd_new;
	int	fd_default;

	fd_default = 0;
	fd_new = -1;
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	dup2(fd_default, fd_min);
	if (ft_strequ(ast_tree->right->content->content, "-"))
		close(fd_default);
	else
	{
		if (ft_isnumber(ast_tree->right->content->content)
				&& ft_atoi(ast_tree->right->content->content) > 9)
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content->content, 2);
			ft_putendl_fd(": illegal file descriptor name", 2);
			if (in_fork)
				exit(1);
			else
				return ;
		}
		else if (ft_isnumber(ast_tree->right->content->content) &&
				(fd_new = dup(ft_atoi(ast_tree->right->content->content))) == -1)
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content->content, 2);
			ft_putendl_fd(": Bad file descriptor", 2);
			if (in_fork)
				exit(1);
			else
				return ;
		}
		else if (!ft_isnumber(ast_tree->right->content->content))
		{
			ft_putstr_fd("lsh: ", 2);
			ft_putstr_fd(ast_tree->right->content->content, 2);
			ft_putendl_fd(": ambiguous redirect", 2);
			if (in_fork)
				exit(1);
			else
				return ;
		}
		dup2(fd_default, fd_new);
		close(fd_default);
	}
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER && ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, fd_min + 1);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, fd_min + 1);
	dup2(fd_min, fd_default);
	close(fd_new);
}

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

void	launch_builtin(char	**cmd)
{
	if (ft_strequ(cmd[0], "unsetenv"))
		ft_unsetenv(cmd + 1);
	else if (ft_strequ(cmd[0], "setenv"))
		ft_setenv(cmd + 1);
	else if (ft_strequ(cmd[0], "cd"))
		ft_cd(cmd);
	else if (ft_strequ(cmd[0], "echo"))
		ft_echo(cmd);
}

int		main_exec(t_ast_node *ast_tree, int in_fork, int fd_min)
{
	char	**cmd;
	char	*tmp;
	pid_t	child;
	char	*builtins[] =
			{"cd", "echo", /*"exit", "env", */"setenv", "unsetenv", NULL};

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
		run_greatand(ast_tree, in_fork, fd_min);
	else if (ast_tree->type == LESSAND)
		run_lessand(ast_tree, in_fork, fd_min);
	else
	{
		cmd = list_to_array(ast_tree->content);
		tmp = ft_strdup(cmd[0]);
		if (!ft_strcmp(cmd[0], "wc") || !ft_strcmp(cmd[0], "sort") ||
				!ft_strcmp(cmd[0], "less") || !ft_strcmp(cmd[0], "env"))
		{	
			free(cmd[0]);
			cmd[0] = ft_strjoin("/usr/bin/", tmp);
		}
		else if (!ft_isinarray(cmd[0], builtins))
		{
			free(cmd[0]);
			cmd[0] = ft_strjoin("/bin/", tmp);
		}
		if (in_fork && !ft_isinarray(cmd[0], builtins))
			execve(cmd[0], cmd, NULL);
		else if (!ft_isinarray(cmd[0], builtins))
		{
			child = fork();
			if (child == 0)
				execve(cmd[0], cmd, g_env);
			else
				wait(NULL);
		}
		else
			launch_builtin(cmd);
	}
	return (0);
}

int		execution(t_ast_node *ast_tree, char **env)
{
	(void)env;
	//print_my_ast(ast_tree, 0, 0);
	main_exec(ast_tree, 0, 10);
	return (0);
}
