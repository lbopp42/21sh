/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/09 11:43:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <time.h>

char	*before_curr_after(char **before, char **curr, char **after)
{
	char	*line;

	line = ft_strnew(0);
	if (*before)
		line = ft_stradd(line, *before);
	line = ft_stradd(line, *curr);
	if (*after)
		line = ft_stradd(line, *after);
	ft_strdel(before);
	ft_strdel(curr);
	ft_strdel(after);
	return (line);
}

void	join_free_all(char **date, int do_itoa)
{
	char	*to_free;

	to_free = ft_itoa(do_itoa);
	*date = ft_stradd(*date, to_free);
	ft_strdel(&to_free);
}

char	*return_date(void)
{
	struct tm	current;
	char		*date;
	static char	*day_array[7] =
		{"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	static char	*month_array[12] = {" Jan ", " Feb ", " Mar ", " Apr ", " May ",
		" Jun ", " Jul ", " Aug ", " Sep ", " Oct ", " Nov ", " Dec "};
	time_t		t;

	time(&t);
	current = *localtime(&t);
	date = ft_strdup(day_array[current.tm_wday]);
	date = ft_stradd(date, month_array[current.tm_mon]);
	join_free_all(&date, current.tm_mday);
	return (date);
}

char	*get_date_prompt(char **line, int *i)
{
	char		*date;
	char		*after;
	char		*before;

	date = return_date();
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	*i += 2 + ft_strlen(date);
	ft_strdel(line);
	*line = before_curr_after(&before, &date, &after);
	return (NULL);
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

char	*get_uid_prompt(void)
{
	uid_t	uid;
	char	*uid_string;

	uid = getuid();
	if (uid == 0)
		uid_string = ft_strdup("#");
	else
		uid_string = ft_strdup("$");
	return (uid_string);
}

char	*get_octal_value(char *code)
{
	char	*octal;
	char	tmp[2];
	int		int_octal;
	int		i;
	int		j;

	int_octal = 0;
	octal = NULL;
	tmp[1] = '\0';
	i = 0;
	j = 2;
	if (code[0] && code[1] && code[2] && ft_isdigit(code[0]) &&
			ft_isdigit(code[1]) && ft_isdigit(code[2]))
	{
		while (i < 3)
		{
			tmp[0] = code[i];
			int_octal += ft_atoi(tmp) * ft_power(8, j);
			j--;
			i++;
		}
		octal = ft_itoa(int_octal);
	}
	return (octal);
}

char	*get_prompt(char **line, int *i)
{
	if ((*line)[*i + 1] == 'd')
		get_date_prompt(line, i);
	/*if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'h')
		printf("%s\n", get_hostname_prompt(1));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'H')
		printf("%s\n", get_hostname_prompt(2));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'l')
		printf("%s\n", get_ttyname());
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 's')
		printf("%s\n", "42sh");
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 't')
		printf("%s\n", get_time_prompt(1));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'T')
		printf("%s\n", get_time_prompt(2));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == '@')
		printf("%s\n", get_time_prompt2());
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'u')
		printf("%s\n", get_username());
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'v')
		printf("%s\n", "1.0");
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'V')
		printf("%s\n", "1.0.0");
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'w')
		printf("%s\n", get_path(1));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'W')
		printf("%s\n", get_path(2));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == '$')
		printf("%s\n", get_uid_prompt());
	if (code[i] == '\\' && code[i + 1] && ft_isdigit(code[i + 1]))
		printf("octal = [%s]\n", get_octal_value(&code[i + 1]));
	if (code[i] == '\\' && code[i + 1] && code[i + 1] == '\\')
		printf("\\");*/
	return (NULL);
}

char	*prompt_management(char *line)
{
	int		i;
	char	tmp[2];

	i = 0;
	tmp[1] = '\0';
	while (line[i])
	{
		if (line[i] == '\\' && line[i + 1])
			get_prompt(&line, &i);
		if (line[i])
			i++;
	}
	return (line);
}

int		main(int ac, char **av)
{
	char	*line;

	(void)ac;
	line = prompt_management(av[1]);
	ft_putendl(line);
	ft_strdel(&line);
	return (0);
}
