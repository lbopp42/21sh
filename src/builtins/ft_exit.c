/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 10:07:15 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/16 16:33:22 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		ft_exit(char **cmd)
{
	int	i;

	ft_putendl_fd("exit", 2);
	if (cmd[1])
	{
		i = 0;
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
			{
				ft_putstr_fd("lsh: exit: ", 2);
				ft_putstr_fd(cmd[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(255);
			}
			i += 1;
		}
		exit(ft_atoi(cmd[1]));
	}
	else
	{
		default_term();
		exit(g_last_status);
	}
	return (1);
}
