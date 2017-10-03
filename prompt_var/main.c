/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/03 16:51:51 by lbopp            ###   ########.fr       */
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

char	*get_time_prompt(int mode)
{
	char	*curr_time;
	time_t		t;
	struct tm	current;
	int			hour;

	time(&t);
	current = *localtime(&t);
	hour = current.tm_hour;
	if (mode != 1 && hour > 12)
		hour -= 12;
	curr_time = ft_strdup(ft_itoa(hour));
	curr_time = ft_stradd(curr_time, ":");
	curr_time = ft_stradd(curr_time, ft_itoa(current.tm_min));
	curr_time = ft_stradd(curr_time, ":");
	curr_time = ft_stradd(curr_time, ft_itoa(current.tm_sec));
	return (curr_time);
}

char	*get_time_prompt2(void)
{
	char	*curr_time;
	time_t		t;
	struct tm	current;
	int			hour;

	time(&t);
	current = *localtime(&t);
	hour = current.tm_hour;
	if (hour > 12)
		hour -= 12;
	curr_time = ft_strdup(ft_itoa(hour));
	curr_time = ft_stradd(curr_time, ":");
	curr_time = ft_stradd(curr_time, ft_itoa(current.tm_min));
	if (current.tm_hour < 12)
		curr_time = ft_stradd(curr_time, " AM");
	else
		curr_time = ft_stradd(curr_time, " PM");
	return (curr_time);
}

char	*get_username(void)
{
	char	*username;

	if (!(username = ft_memalloc(sizeof(char) * 257)))
		exit(EXIT_FAILURE);
	getlogin_r(username, 256);
	return (username);
}

char	*get_path(int mode)
{
	char	path[256];
	char	*final_path;

	getcwd(path, 256);
	final_path = ft_strdup(path);
	if (mode == 2)
		final_path = ft_strrchr(final_path, '/');
	if (final_path[0] && final_path[0] == '/')
		final_path++;
	return (final_path);
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
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 's')
			printf("%s\n", "42sh");
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 't')
			printf("%s\n", get_time_prompt(1));
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'T')
			printf("%s\n", get_time_prompt(2));
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == '@')
			printf("%s\n", get_time_prompt2());
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'u')
			printf("%s\n", get_username());
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'v')
			printf("%s\n", "1.0");
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'V')
			printf("%s\n", "1.0.0");
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'w')
			printf("%s\n", get_path(1));
		else if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'W')
			printf("%s\n", get_path(2));
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
