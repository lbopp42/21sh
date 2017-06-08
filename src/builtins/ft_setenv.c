/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 11:01:13 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 11:11:27 by lbopp            ###   ########.fr       */
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
		(*env)->name = ft_strdup(var);
		(*env)->content = ft_strdup(valeur);
		(*env)->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_lst*)malloc(sizeof(t_lst))))
			return ;
		tmp->next->name = ft_strdup(var);
		tmp->next->content = ft_strdup(valeur);
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
			tmp->content = ft_strdup(valeur);
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp && !ft_strcmp(tmp->name, var))
	{
		free(tmp->content);
		tmp->content = ft_strdup(valeur);
		return ;
	}
	fill_env(env, var, valeur);
}

void	ft_setenv(char **cmd)
{
	t_lst	*env;
	int		i;

	i = 1;
	env = tab_to_list(g_env);
	if (!cmd[1] || !cmd[2])
	{
		ft_putstr_fd("lsh: setenv: Too few argument\n", 2);
		return ;
	}
	while (cmd[i] && cmd[i + 1])
	{
		put_in_env(&env, cmd[i], cmd[i + 1]);
		i += 2;
	}
	g_env = list_to_tab(env);
}
