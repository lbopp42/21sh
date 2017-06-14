/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:01:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/14 11:02:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	fill_env(t_lst **env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = *env;
	if (!tmp)
	{
		if (!(*env = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		(*env)->name = var ? ft_strdup(var) : NULL;
		(*env)->content = valeur ? ft_strdup(valeur) : NULL;
		(*env)->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		tmp->next->name = var ? ft_strdup(var) : NULL;
		tmp->next->content = valeur ? ft_strdup(valeur) : NULL;
		tmp->next->next = NULL;
	}
}

void	put_in_env(t_lst **env, char *var, char *valeur)
{
	t_lst	*tmp;

	tmp = *env;
	while (tmp && tmp->next != NULL)
	{
		if (!ft_strcmp(tmp->name, var))
		{
			free(tmp->content);
			tmp->content = valeur ? ft_strdup(valeur) : NULL;
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp && !ft_strcmp(tmp->name, var))
	{
		free(tmp->content);
		tmp->content = valeur ? ft_strdup(valeur) : NULL;
		return ;
	}
	fill_env(env, var, valeur);
}

int		ft_setenv(char **cmd)
{
	t_lst	*env;

	env = tab_to_list(g_env);
	if (!cmd[0] || !cmd[1])
	{
		ft_putstr_fd("lsh: setenv: Too few argument\n", 2);
		return (1);
	}
	put_in_env(&env, cmd[0], cmd[1]);
	g_env = list_to_tab(env);
	return (0);
}
