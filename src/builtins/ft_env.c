/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:42:02 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/14 16:15:59 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		check_opt_env(char **cmd, int *option)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] == '-')
		{
			*option = 1;
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'i')
				{
					ft_putstr_fd("env: illegal option -- ", 2);
					ft_putchar_fd(cmd[i][j], 2);
					ft_putstr_fd("\nusage: env [-i] ", 2);
					ft_putendl_fd("[name=value ...] [utility [argument ...]]", 2);
					return (-1);
				}
				j += 1;
			}
		}
		else
			break;
		i += 1;
	}
	return (i);
}

void	print_env(t_lst *env)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putchar('=');
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

t_list	*array_to_list(char **cmd)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	lst = (t_list*)ft_memalloc(sizeof(t_list));
	lst->content = ft_strdup(cmd[0]);
	tmp = lst;
	i = 0;
	while (cmd[i + 1])
	{
		tmp->next = (t_list*)ft_memalloc(sizeof(t_list));
		tmp->next->content = ft_strdup(cmd[i + 1]);
		tmp = tmp->next;
		i += 1;
	}
	tmp = NULL;
	return (lst);
}

void	var_in_env(char *cmd, t_lst **env)
{
	int		i;
	char	*name;
	char	*valeur;

	i = 0;
	while (cmd[i] != '=')
		i += 1;
	name = ft_strsub(cmd, 0, i);
	valeur = ft_strchr(cmd, '=') + 1;
	put_in_env(env, name, valeur);
	ft_strdel(&name);
}

int		ft_env(char **cmd, int in_fork)
{
	int		i;
	int		option;
	t_lst	*env;
	t_list	*cmd_list;
	pid_t	child;

	option = 0;
	i = check_opt_env(cmd, &option);
	if (i == -1)
		return (1);
	child = in_fork ? 0 : fork();
	if (child == 0)
	{
		env = option ? NULL : tab_to_list(g_env);
		while (cmd[i])
		{
			if (ft_strchr(cmd[i], '='))
				var_in_env(cmd[i], &env);
			else
				break ;
			i += 1;
		}
		if (!cmd[i])
		{
			print_env(env);
			exit(0);
		}
		else
		{
			cmd_list = array_to_list(&cmd[i]);
			//Completer de PATH (ls -> /bin/ls) avant d'envoyer
			//Attention si on a un PATH=... il faut use ce nouveau path
			g_env = list_to_tab(env);
			del_lst(env);
			execution_cmd(cmd_list, 1);
		}
	}
	else
		wait(NULL);
	return (0);
}
