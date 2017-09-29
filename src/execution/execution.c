/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 09:40:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/29 10:25:56 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int		print_error_fork(char *content, char *error, int in_fork)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(content, 2);
	ft_putendl_fd(error, 2);
	if (in_fork)
		exit(1);
	else
		return (1);
	return (0);
}

void		print_error(char *content, char *error)
{
	ft_putstr_fd("lsh: ", 2);
	ft_putstr_fd(content, 2);
	ft_putendl_fd(error, 2);
}

void	run_redir_great(t_ast_node *ast_tree, int in_fork)
{
	int			new_fd;
	int			tmp_out;
	static	int	first = 0;
	int			fd_default;

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
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER &&
			ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, 10);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, 10);
	close(fd_default);
	dup2(tmp_out, fd_default);
	first = 0;
}

void	run_redir_dgreat(t_ast_node *ast_tree, int in_fork)
{
	int			new_fd;
	static	int	first = 0;
	int			tmp_out;
	int			fd_default;

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
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER &&
			ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, 10);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, 10);
	close(fd_default);
	first = 0;
	dup2(tmp_out, fd_default);
}

void	run_redir_less(t_ast_node *ast_tree, int in_fork)
{
	int			new_fd;
	static	int	first = 0;
	int			tmp_in;
	int			fd_default;

	fd_default = 0;
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER)
		fd_default = ft_atoi(ast_tree->left->content->content);
	new_fd = open(ast_tree->right->content->content,
			O_RDONLY, S_IRUSR | S_IWUSR);
	tmp_in = dup(fd_default);
	if (new_fd == -1)
		if (print_error_fork(ast_tree->right->content->content,
					": No such file or directory", in_fork))
			return ;
	if (first == 0)
	{
		dup2(new_fd, fd_default);
		first = 1;
	}
	close(new_fd);
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER &&
			ast_tree->left->left)
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
			if (print_error_fork(ast_tree->right->content->content,
					": illegal file descriptor name", in_fork))
				return ;
		}
		else if (ft_isnumber(ast_tree->right->content->content)
				&& (fd_new =
				dup(ft_atoi(ast_tree->right->content->content))) == -1)
		{
			if (print_error_fork(ast_tree->right->content->content,
					": Bad file descriptor", in_fork))
				return ;
		}
		else if (!ft_isnumber(ast_tree->right->content->content))
			fd_new = open(ast_tree->right->content->content,
					O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		dup2(fd_default, fd_new);
		close(fd_default);
	}
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER &&
			ast_tree->left->left)
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
			if (print_error_fork(ast_tree->right->content->content,
					": illegal file descriptor name", in_fork))
				return ;
		}
		else if (ft_isnumber(ast_tree->right->content->content) &&
				(fd_new = dup(ft_atoi(
				ast_tree->right->content->content))) == -1)
		{
			if (print_error_fork(ast_tree->right->content->content,
					": Bad file descriptor", in_fork))
				return ;
		}
		else if (!ft_isnumber(ast_tree->right->content->content))
			if (print_error_fork(ast_tree->right->content->content,
					": ambiguous redirect", in_fork))
				return ;
		dup2(fd_default, fd_new);
		close(fd_default);
	}
	if (ast_tree->left && ast_tree->left->type == IO_NUMBER &&
			ast_tree->left->left)
		main_exec(ast_tree->left->left, in_fork, fd_min + 1);
	else if (ast_tree->left)
		main_exec(ast_tree->left, in_fork, fd_min + 1);
	dup2(fd_min, fd_default);
	close(fd_new);
}

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
	else if (child > 0)
	{
		dup2(p[READ_END], STDIN_FILENO);
		close(p[WRITE_END]);
		close(p[READ_END]);
		main_exec(ast_tree->right, 1, 10);
	}
}

void	launch_pipe(t_ast_node *ast_tree)
{
	pid_t		child;
	pid_t		child2;
	int			p[2];
	static int	fork_nb = 0;

	if (fork_nb == 0)
	{
		fork_nb = 1;
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
		{
			child2 = fork();
			if (child2 == 0)
			{
				dup2(p[READ_END], STDIN_FILENO);
				close(p[WRITE_END]);
				close(p[READ_END]);
				main_exec(ast_tree->right, 1, 10);
			}
			if (child2 > 0)
			{
				close(p[WRITE_END]);
				close(p[READ_END]);
				wait(NULL);
				wait(NULL);
				fork_nb = 0;
			}
		}
	}
	else
		run_pipe(ast_tree);
}

void	launch_builtin(char **cmd, int in_fork)
{
	if (ft_strequ(cmd[0], "unsetenv"))
		g_last_status = ft_unsetenv(cmd + 1);
	else if (ft_strequ(cmd[0], "setenv"))
		g_last_status = ft_setenv(cmd + 1);
	else if (ft_strequ(cmd[0], "cd"))
		g_last_status = ft_cd(cmd);
	else if (ft_strequ(cmd[0], "echo"))
		g_last_status = ft_echo(cmd);
	else if (ft_strequ(cmd[0], "exit"))
	{
		free_tuple(&g_tuple);
		save_history();
		default_term();
		g_last_status = ft_exit(cmd);
	}
	else if (ft_strequ(cmd[0], "env"))
		g_last_status = ft_env(cmd, in_fork);
	if (in_fork)
		exit(0);
}

int		verif_path(char *path, char *perm, char **cmd)
{
	if (!path && perm)
		print_error(perm, ": Permission denied");
	else if (!path && !perm)
		print_error(*cmd, ": command not found");
	else if (path)
	{
		ft_strdel(cmd);
		*cmd = ft_strdup(path);
		return (1);
	}
	return (0);
}

int		find_abs_path(char **cmd, char *path)
{
	char		**paths;
	char		*perm;
	int			i;
	struct stat	st;

	perm = NULL;
	if ((*cmd)[0] != '/' && (*cmd)[0] != '.' && path && ft_strlen(path))
	{
		i = 0;
		paths = ft_strsplit(path, ':');
		while (paths[i])
		{
			paths[i] = ft_addslash(paths[i], *cmd);
			if (!access(paths[i], F_OK))
			{
				if (!access(paths[i], X_OK))
					break ;
				else
					perm = perm ? perm : paths[i];
			}
			i += 1;
		}
		if (!verif_path(paths[i], perm, cmd))
		{
			del_array(paths);
			return (0);
		}
		del_array(paths);
	}
	else if ((*cmd)[0] == '.' || (*cmd)[0] == '/' || !path || !ft_strlen(path))
	{
		if (!access(*cmd, F_OK))
		{
			lstat(cmd[0], &st);
			if (S_ISDIR(st.st_mode))
			{
				print_error(*cmd, ": is a directory");
				return (0);
			}
			else if (access(*cmd, X_OK))
			{
				print_error(*cmd, ": Permission denied");
				return (0);
			}
		}
		else
		{
			print_error(*cmd, ": No such file or directory");
			return (0);
		}
	}
	return (1);
}

void	execution_cmd(t_list *content, int in_fork, char *path)
{
	char		**cmd;
	pid_t		child;
	static char	*builtins[] =
	{"cd", "echo", "exit", "env", "setenv", "unsetenv", NULL};

	cmd = list_to_array(content);
	if (ft_isinarray(cmd[0], builtins))
		launch_builtin(cmd, in_fork);
	else if (cmd[0] && cmd[0][0])
	{
		if (!find_abs_path(&cmd[0], path))
			return ;
		if (in_fork)
			execve(cmd[0], cmd, g_env);
		else
		{
			child = fork();
			if (child == 0)
				execve(cmd[0], cmd, g_env);
			else
			{
				del_array(cmd);
				wait(NULL);
			}
		}
	}
	else
		print_error(*cmd, ": command not found");
	del_array(cmd);
}

/*
**	Array of funct is possible
*/

int		main_exec(t_ast_node *ast_tree, int in_fork, int fd_min)
{
	if (!ast_tree)
		return (0);
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
		execution_cmd(ast_tree->content, in_fork, get_var_content("PATH"));
	return (0);
}

int		execution(t_ast_node *ast_tree, char **env)
{
	(void)env;
	main_exec(ast_tree, 0, 10);
	return (0);
}
