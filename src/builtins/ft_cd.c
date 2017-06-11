/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 10:50:30 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/11 13:14:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	add_slash(char **content)
{
	if ((*content)[ft_strlen(*content)] != '/')
		*content = ft_stradd(*content, "/");
}

char	*edit_path(char *content, char *pwd)
{
	int	i;
	int	j;
	char tmp[2];
	int		found;

	i = 0;
	tmp[1] = 0;
	found = 0;
	pwd = ft_strdup(pwd);
	while (content[i])
	{
		if (content[i] && content[i + 1] &&
				content[i] == '.' && content[i + 1] == '.')
		{
			if (ft_strcmp(pwd, "/"))
			{
				j = ft_strlen(pwd) - 1;
				while (pwd[j] == '/')
					j -= 1;
				while (pwd[j] != '/')
					j -= 1;
				pwd = ft_strsub(pwd, 0, j);
				add_slash(&pwd);
			}
			i += 2;
		}
		else if (content[i] == '.')
			i += 1;
		else if (content[i] == '/')
		{
			pwd = ft_stradd(pwd, "/");
			while (content[i + 1] && content[i + 1] == '/')
				i += 1;
		}
		else
		{
			if (found == 0)
			{
				add_slash(&pwd);
			}
			found = 1;
			tmp[0] = content[i];
			pwd = ft_stradd(pwd, tmp);
		}
		i += 1;
	}
	return (pwd);
}

int		exec_cd(char *cmd, int option, t_lst **env);

void	exec_cd_cdpath(char	*cmd, t_lst **env, char *cdpath, int option)
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

int		exec_cd(char *cmd, int option, t_lst **env)
{
	char	pwd[256];
	char	*new_pwd;

	// When we follow the symbolic link
	if (option == 1)
	{
		if (chdir(cmd) == -1)
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": No such directory", 2);
		}
		else
		{
			put_in_env(env, "OLDPWD", get_var_content("PWD"));
			getcwd(pwd, 256);
			put_in_env(env, "PWD", pwd);
			return (0);
		}
	}
	else
	{
		getcwd(pwd, 256);
		new_pwd = edit_path(cmd, pwd);
		if (chdir(new_pwd) == -1)
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd(": No such directory", 2);
		}
		else
		{
			put_in_env(env, "OLDPWD", get_var_content("PWD"));
			put_in_env(env, "PWD", new_pwd);
			return (0);
		}
	}
	return (1);
}

int		ft_cd(char **cmd)
{
	char	*home_var;
	char	pwd[256];
	t_lst	*env;
	char	*cdpath;

	home_var = get_var_content("HOME");
	getcwd(pwd, 256);
	env = tab_to_list(g_env);
	if (!cmd[1] && (!home_var || !ft_strlen(home_var)))
		ft_putstr_fd("lsh: cd: HOME not set\n", 2);
	else if (!cmd[1] && home_var)
	{
		if (chdir(home_var) == -1)
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(home_var, 2);
			ft_putendl_fd(": No such directory", 2);
		}
		else
		{
			put_in_env(&env, "OLDPWD", pwd);
			getcwd(pwd, 256);
			put_in_env(&env, "PWD", pwd);
		}
	}
	else if (cmd[1] && cmd[1][0] == '/')
	{
		if (chdir(cmd[1]) == -1)
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(": No such directory", 2);
		}
		else
		{
			put_in_env(&env, "OLDPWD", pwd);
			put_in_env(&env, "PWD", cmd[1]);
		}
	}
	else if (cmd[1] && cmd[1][0] == '.')
	{
		if (chdir(cmd[1]) == -1)
		{
			ft_putstr_fd("lsh: cd: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putendl_fd(": No such directory", 2);
		}
		else
		{
			put_in_env(&env, "OLDPWD", pwd);
			getcwd(pwd, 256);
			put_in_env(&env, "PWD", pwd);
		}
	}
	else
	{
		if (!(cdpath = get_var_content("CDPATH")))
			exec_cd(cmd[1], 2, &env);
		else
			exec_cd_cdpath(cmd[1], &env, cdpath, 1);
	}
	g_env = list_to_tab(env);
	return (0);
	//cd utilise CDPATH pour se deplacer !
}
