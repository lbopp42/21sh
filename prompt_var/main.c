/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 10:28:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/10/03 11:14:15 by lbopp            ###   ########.fr       */
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

char	*get_prompt(char *code)
{
	int	i;

	i = 0;
	while (code[i])
	{
		if (code[i] == '\\' && code[i + 1] && code[i + 1] == 'd')
			printf("%s\n", get_date_prompt());
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
