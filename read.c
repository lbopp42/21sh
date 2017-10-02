/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:08:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/02 14:16:17 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}

/*
**	read avec le -r
**	Il faut juste stocker dans variable local
*/

char	*read_r_opt(char **cmd)
{
	char	buf[2];
	char	*readding;

	init_term();
	readding = ft_strnew(0);
	while (1)
	{
		ft_bzero(buf, 2);
		read(0, buf, 2);
		if (buf[0] == 10)
			break ;
		else if (buf[0] == 127 && !buf[1])
		{
			if (readding)
			{
				tputs(tgetstr("le", NULL), 1, &put_my_char);
				tputs(tgetstr("cd", NULL), 1, &put_my_char);
				readding[ft_strlen(readding) - 1] = '\0';
			}
		}
		else if (ft_isprint(buf[0]) && !buf[1])
		{
			ft_putchar(buf[0]);
			readding = ft_stradd(readding, buf);
		}
	}
	default_term();
	return (readding);
}

int		get_read_opt(char **cmd)
{
	int	size;
	int	ret;
	int	opt;

	opt = 0;
	size = 0;
	while (cmd[size])
		size++;
	while ((ret = ft_getopt(size, (const char**)cmd, "r")) != -1)
		opt = ret;
	return (opt);
}

int		valid_local_var(char **cmd)
{
	return (1);
}

void	read_put_in_var(char **cmd, char *readding)
{
	char	**split;
	int		i;

	i = 0;
	if (!cmd[g_optind] || !valid_local_var(&cmd[g_optind]))
		return ;
	split = ft_strsplit(readding, ' ');
	printf("\n");
	while (cmd[g_optind + 1])
	{
		if ()
		printf("%s = [%s]\n", cmd[g_optind], split[i]);
		g_optind++;
		i++;
	}
	while (split[i])
	{
		printf("ajout de [%s] a %s\n", split[i], cmd[g_optind]);
		i++;
	}
}

void	ft_read(char **cmd, char **env)
{
	int		opt;
	char	*readding;

	opt = get_read_opt(cmd);
	if (opt != 0 && opt != 'r')
	{
		printf("ERROR\n");
		return ;
	}
	if (opt == 'r')
		readding = read_r_opt(cmd);
	read_put_in_var(cmd, readding);
}

int	main(int ac, char **av, char **env)
{
	ft_read(av + 1, env);
}
