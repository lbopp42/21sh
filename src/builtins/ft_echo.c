/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 13:01:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/14 11:03:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		isa(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == 'a')
	{
		ft_putchar('\a');
		return (1);
	}
	return (0);
}

int		isr(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == 'r')
	{
		ft_putchar('\r');
		return (1);
	}
	return (0);
}

int		isn(char *c)
{
	if (*c == 92 && *c + 1 && *(c + 1) == 'n')
	{
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

int		ist(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == 't')
	{
		ft_putchar('\t');
		return (1);
	}
	return (0);
}

int		isv(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == 'v')
	{
		ft_putchar('\v');
		return (1);
	}
	return (0);
}

int		isbackslash(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == '\\')
	{
		ft_putchar('\\');
		return (1);
	}
	return (0);
}

int		isf(char *c)
{
	if (*c == '\\' && *c + 1 && *(c + 1) == 'f')
	{
		ft_putchar('\f');
		return (1);
	}
	return (0);
}

int		isother(char *c)
{
	ft_putchar(*c);
	return (0);
}

int		ft_echo(char **cmd)
{
	int				i;
	int				j;
	int				k;
	static int		(*back_func[])(char *c) =
	{&isa, &isr, &isn, &ist, &isv, &isbackslash, &isf, &isother};

	i = 0;
	while (cmd[++i])
	{
		i != 1 ? ft_putchar(' ') : 0;
		j = -1;
		while (cmd[i][++j])
		{
			k = 0;
			if (cmd[i][j] == '\\' && cmd[i][j + 1] && cmd[i][j + 1] == 'c')
				return (0);
			while (k < 8 && cmd[i][j])
				if (back_func[k++](&cmd[i][j]))
				{
					j += 1;
					break ;
				}
		}
	}
	ft_putchar('\n');
	return (0);
}
