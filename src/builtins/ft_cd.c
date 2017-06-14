/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:50:30 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/14 13:17:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	add_slash(char **content)
{
	if ((*content)[ft_strlen(*content)] != '/')
		*content = ft_stradd(*content, "/");
}

void	edit_path_dotdot(char **pwd, int *i)
{
	int	j;

	if (ft_strcmp(*pwd, "/"))
	{
		j = ft_strlen(*pwd) - 1;
		while ((*pwd)[j] == '/')
			j -= 1;
		while ((*pwd)[j] != '/')
			j -= 1;
		*pwd = ft_strsub(*pwd, 0, j);
		add_slash(pwd);
	}
	*i += 2;
}

void	edit_path2(char *content, char **pwd, int *i)
{
	static int	found = 0;
	char		tmp[2];

	tmp[1] = 0;
	if (content[*i] && content[*i + 1] &&
			content[*i] == '.' && content[*i + 1] == '.')
		edit_path_dotdot(pwd, i);
	else if (content[*i] == '.')
		*i += 1;
	else if (content[*i] == '/')
	{
		*pwd = ft_stradd(*pwd, "/");
		while (content[*i + 1] && content[*i + 1] == '/')
			*i += 1;
	}
	else
	{
		!found ? add_slash(pwd) : 0;
		found = 1;
		tmp[0] = content[*i];
		*pwd = ft_stradd(*pwd, tmp);
	}
}

char	*edit_path(char *content, char *pwd)
{
	int		i;

	i = 0;
	pwd = ft_strdup(pwd);
	while (content[i])
	{
		edit_path2(content, &pwd, &i);
		i += 1;
	}
	return (pwd);
}

int		exec_cd(char *cmd, int option, t_lst **env);

void	exec_cd_cdpath(char *cmd, t_lst **env, char *cdpath, int option)
{
	char	**cdpath_split;
	int		i;
	char	*new_path;

	cdpath_split = ft_strsplit(cdpath, ':');
	i = 0;
	while (cdpath_split[i])
	{
		add_slash(&cdpath_split[i]);
		new_path = ft_strjoin(cdpath_split[i], cmd);
		if (!exec_cd(new_path, option, env))
			return ;
		i += 1;
	}
	ft_putstr_fd("lsh: cd: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such directory", 2);
}

int		exec_chdir(char *cmd, char *pwd, t_lst **env)
{
	char	pwd_tab[256];

	if (chdir(cmd) == -1)
	{
		ft_putstr_fd("lsh: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such directory", 2);
		return (1);
	}
	else
	{
		put_in_env(env, "OLDPWD", get_var_content("PWD"));
		if (!pwd)
		{
			getcwd(pwd_tab, 256);
			put_in_env(env, "PWD", pwd_tab);
		}
		else
			put_in_env(env, "PWD", pwd);
	}
	return (0);
}

int		exec_cd(char *cmd, int option, t_lst **env)
{
	char	pwd[256];
	char	*new_pwd;

	if (option == 80)
		exec_chdir(cmd, NULL, env);
	else
	{
		getcwd(pwd, 256);
		new_pwd = edit_path(cmd, pwd);
		exec_chdir(new_pwd, new_pwd, env);
		free(new_pwd);
	}
	return (1);
}

int		parser_cd_opt(char **cmd)
{
	int i;
	int	j;

	i = 1;
	g_optopt = 0;
	while (cmd[i] && cmd[i][0] == '-')
	{
		j = 1;
		if (!cmd[i][j])
			return (i);
		else if (cmd[i][j] == '-' && !cmd[i][j + 1])
			return (i + 1);
		else if (cmd[i][j] == 'L' || cmd[i][j] == 'P')
			g_optopt = cmd[i][j];
		else
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd(": invalid option\ncd: usage: cd [-L|-P] [dir]", 2);
			return (-1);
		}
		i += 1;
	}
	return (i);
}

int		exec_without_cdpath(char *cmd, t_lst **env)
{
	char *home_var;

	home_var = get_var_content("HOME");
	if (!cmd && (!home_var || !ft_strlen(home_var)))
		ft_putstr_fd("lsh: cd: HOME not set\n", 2);
	else if (!cmd && home_var)
		exec_chdir(home_var, NULL, env);
	else if (ft_strequ(cmd, "-") && !get_var_content("OLDPWD"))
		ft_putendl_fd("lsh: cd: OLDPWD not set", 2);
	else if (ft_strequ(cmd, "-"))
	{
		ft_putendl(get_var_content("OLDPWD"));
		exec_chdir(get_var_content("OLDPWD"), NULL, env);
	}
	else if (cmd && cmd[0] == '/')
		exec_chdir(cmd, cmd, env);
	else if (cmd && cmd[0] == '.')
		exec_chdir(cmd, cmd, env);
	else
		return (0);
	return (1);
}

int		ft_cd(char **cmd)
{
	t_lst	*env;
	char	*cdpath;
	int		i;

	i = parser_cd_opt(cmd);
	if (i == -1)
		return (1);
	env = tab_to_list(g_env);
	if (!exec_without_cdpath(cmd[i], &env))
	{
		if (!(cdpath = get_var_content("CDPATH")))
			exec_cd(cmd[i], g_optopt, &env);
		else
			exec_cd_cdpath(cmd[i], &env, cdpath, g_optopt);
	}
	g_env = list_to_tab(env);
	del_lst(env);
	return (0);
}
