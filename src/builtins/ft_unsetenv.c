/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:05:29 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/14 11:01:59 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	remove_var(t_lst *env, char *var)
{
	t_lst	*tmp;
	t_lst	*origin;

	origin = env;
	if (!ft_isenv(env, var))
		return ;
	tmp = origin;
	while (origin != NULL)
	{
		if (!ft_strcmp(origin->name, var))
		{
			free(origin->name);
			free(origin->content);
			if (tmp != NULL)
				tmp->next = origin->next;
			free(origin);
			return ;
		}
		tmp = origin;
		origin = origin->next;
	}
}

int		ft_unsetenv(char **cmd)
{
	t_lst	*lst;

	lst = tab_to_list(g_env);
	if (!cmd[0])
	{
		ft_putendl_fd("lsh: unsetenv: Too few arguments.", 2);
		return (1);
	}
	remove_var(lst, cmd[0]);
	g_env = list_to_tab(lst);
	return (0);
}
