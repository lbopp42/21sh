/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/03 12:48:00 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <time.h>

char	*get_date_prompt(void)
{
	time_t		t;
	struct tm	current;
	static char	*day_array[7] =
		{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	static char	*month_array[12] = {" Jan ", " Feb ", " Mar ", " Apr ", " May ",
		" Jun ", " Jul ", " Aug ", " Sep ", " Oct ", " Nov ", " Dec "};
	char		*date;

	time(&t);
	current = *localtime(&t);
	date = ft_strdup(day_array[current.tm_wday]);
	date = ft_stradd(date, month_array[current.tm_mon]);
	date = ft_stradd(date, ft_itoa(current.tm_mday));
	return (date);
}

char	*get_hostname_prompt(int mode)
{
	char	*hostname;
	char	**split;

	if (!(hostname = ft_memalloc(sizeof(char) * 256)))
		exit (EXIT_FAILURE);
	gethostname(hostname, 256);
	if (mode == 1)
	{
		split = ft_strsplit(hostname, '.');
		ft_strdel(&hostname);
		hostname = ft_strdup(split[0]);
		// FREE split
	}
	return (hostname);
}

char	*get_ttyname(void)
{
	char	*name;

	name = ttyname(0);
	name = ft_strrchr(name, '/');
	if (name[0] && name[0] == '/')
		name++;
	return (name);
}

char	*get_prompt(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'd')
			printf("%s\n", get_date_prompt());
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'h')
			printf("%s\n", get_hostname_prompt(1));
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'H')
			printf("%s\n", get_hostname_prompt(2));
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'l')
			printf("%s\n", get_ttyname());
		i++;
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	(void)ac;
	get_prompt(av[1]);
	return (0);
}
