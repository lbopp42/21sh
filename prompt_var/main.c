/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/09 17:44:58 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <time.h>

char	*before_curr_after(char **before, char *curr, char **after)
{
	char	*line;

	line = ft_strnew(0);
	if (*before)
		line = ft_stradd(line, *before);
	line = ft_stradd(line, curr);
	if (*after)
		line = ft_stradd(line, *after);
	ft_strdel(before);
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

void	get_date_prompt(char **line, int *i)
{
	char		*date;
	char		*after;
	char		*before;

	date = return_date();
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	*i += ft_strlen(date);
	ft_strdel(line);
	*line = before_curr_after(&before, date, &after);
	ft_strdel(&date);
}

void	get_hostname_prompt(char **line, int *i, int mode)
{
	char	*hostname;
	char	**split;
	char	*after;
	char	*before;

	if (!(hostname = ft_memalloc(sizeof(char) * 256)))
		exit (EXIT_FAILURE);
	gethostname(hostname, 256);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	if (mode == 1)
	{
		split = ft_strsplit(hostname, '.');
		ft_strdel(&hostname);
		hostname = ft_strdup(split[0]);
		// FREE split
	}
	*i += ft_strlen(hostname);
	ft_strdel(line);
	*line = before_curr_after(&before, hostname, &after);
	ft_strdel(&hostname);
}

void	get_ttyname(char **line, int *i)
{
	char	*name;
	char	*before;
	char	*after;

	name = ttyname(0);
	name = ft_strrchr(name, '/');
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	if (name[0] && name[0] == '/')
		name++;
	*i += ft_strlen(name);
	ft_strdel(line);
	*line = before_curr_after(&before, name, &after);
}

void	get_time_prompt(char **line, int *i, int mode)
{
	char		*curr_time;
	time_t		t;
	struct tm	current;
	char		*before;
	char		*after;

	time(&t);
	current = *localtime(&t);
	current.tm_hour -= (mode != 1 && current.tm_hour > 12) ? 12 : 0;
	before = ft_itoa(current.tm_hour);
	curr_time = ft_strdup(before);
	curr_time = ft_stradd(curr_time, ":");
	ft_strdel(&before);
	before = ft_itoa(current.tm_min);
	curr_time = ft_stradd(curr_time, before);
	curr_time = ft_stradd(curr_time, ":");
	ft_strdel(&before);
	before = ft_itoa(current.tm_sec);
	curr_time = ft_stradd(curr_time, before);
	ft_strdel(&before);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, curr_time, &after);
	ft_strdel(&curr_time);
}

void	get_time_prompt2(char **line, int *i)
{
	char		*curr_time;
	time_t		t;
	struct tm	current;
	char		*before;
	char		*after;

	time(&t);
	current = *localtime(&t);
	current.tm_hour -= (current.tm_hour > 12) ? 12 : 0;
	before = ft_itoa(current.tm_hour);
	curr_time = ft_strdup(before);
	ft_strdel(&before);
	curr_time = ft_stradd(curr_time, ":");
	before = ft_itoa(current.tm_min);
	curr_time = ft_stradd(curr_time, before);
	ft_strdel(&before);
	if (current.tm_hour < 12)
		curr_time = ft_stradd(curr_time, " AM");
	else
		curr_time = ft_stradd(curr_time, " PM");
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, curr_time, &after);
	ft_strdel(&curr_time);
}

void	get_username(char **line, int *i)
{
	char	*username;
	char	*before;
	char	*after;

	if (!(username = ft_memalloc(sizeof(char) * 257)))
		exit(EXIT_FAILURE);
	getlogin_r(username, 256);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, username, &after);
	ft_strdel(&username);
}

void	get_path(char **line, int *i, int mode)
{
	char	path[256];
	char	*final_path;
	char	*before;
	char	*after;

	getcwd(path, 256);
	if (mode == 2)
		final_path = ft_strrchr(path, '/');
	else
		final_path = ft_strdup(path);
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (final_path[0] && final_path[0] == '/')
		*line = before_curr_after(&before, final_path + 1, &after);
	else
		*line = before_curr_after(&before, final_path, &after);
	if (mode != 2)
		ft_strdel(&final_path);
}

void	get_uid_prompt(char **line, int *i)
{
	uid_t	uid;
	char	*before;
	char	*after;

	uid = getuid();
	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	*i += 1;
	ft_strdel(line);
	if (uid == 0)
		*line = before_curr_after(&before, "#", &after);
	else
		*line = before_curr_after(&before, "$", &after);
}

void	get_octal_value2(char **line, int *i, char **octal)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 4, ft_strlen(*line) - *i - 4);
	ft_strdel(line);
	*i += ft_strlen(*octal);
	*line = before_curr_after(&before, *octal, &after);
	ft_strdel(octal);
}

void	get_octal_value(char **line, int *i, char *code)
{
	char	*octal;
	char	tmp[2];
	int		int_octal;
	int		curs;
	int		j;

	int_octal = 0;
	octal = NULL;
	tmp[1] = '\0';
	curs = 0;
	j = 2;
	if (code[0] && code[1] && code[2] && ft_isdigit(code[0]) &&
			ft_isdigit(code[1]) && ft_isdigit(code[2]))
	{
		while (curs < 3)
		{
			tmp[0] = code[curs];
			int_octal += ft_atoi(tmp) * ft_power(8, j);
			j--;
			curs++;
		}
		octal = ft_itoa(int_octal);
	}
	get_octal_value2(line, i, &octal);
}

void	get_shell_name(char **line, int *i)
{
	char *before;
	char *after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, "42sh", &after);
}

void	get_version(char **line, int *i, int mode)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	if (mode == 1)
		*line = before_curr_after(&before, "1.0", &after);
	else
		*line = before_curr_after(&before, "1.0.0", &after);
}

void	add_backslash(char **line, int *i)
{
	char	*before;
	char	*after;

	before = ft_strsub(*line, 0, *i);
	after = ft_strsub(*line, *i + 2, ft_strlen(*line) - *i - 2);
	ft_strdel(line);
	*line = before_curr_after(&before, "\\", &after);
}

char	*get_prompt(char **line, int *i)
{
	if ((*line)[*i + 1] == 'd')
		get_date_prompt(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'h')
		get_hostname_prompt(line, i, 1);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'H')
		get_hostname_prompt(line, i, 2);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'l')
		get_ttyname(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 's')
		get_shell_name(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 't')
		get_time_prompt(line, i, 1);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'T')
		get_time_prompt(line, i, 2);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '@')
		get_time_prompt2(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'u')
		get_username(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'v')
		get_version(line, i, 1);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'V')
		get_version(line, i, 2);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'w')
		get_path(line, i, 1);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == 'W')
		get_path(line, i, 2);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '$')
		get_uid_prompt(line, i);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && ft_isdigit((*line)[*i + 1]))
		get_octal_value(line, i, &(*line)[*i + 1]);
	if ((*line)[*i] == '\\' && (*line)[*i + 1] && (*line)[*i + 1] == '\\')
		add_backslash(line, i);
	return (NULL);
}

void	prompt_management(char **line)
{
	int		i;
	char	tmp[2];

	i = 0;
	tmp[1] = '\0';
	while ((*line)[i])
	{
		if ((*line)[i] == '\\' && (*line)[i + 1])
			get_prompt(line, &i);
		if ((*line)[i])
			i++;
	}
}

int		main(int ac, char **av)
{
	char	*line;

	(void)ac;
	line = ft_strdup(av[1]);
	printf("ON RECOIS [%s]\n", line);
	prompt_management(&line);
	ft_putendl(line);
	ft_strdel(&line);
	return (0);
}
