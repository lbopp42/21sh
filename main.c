/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:02:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/24 11:02:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		isblank(int *i)
{
	if (ft_isspace(g_line[*i]))
		return (BLANK);
	return (WORD);
}

int		isop(int *i)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};
	int			id;
	size_t		max;
	int			ret;

	id = 0;
	max = 0;
	ret = WORD;
	while (token[id])
	{
		if (!ft_strncmp(&g_line[*i], token[id], ft_strlen(token[id])))
			if (max < ft_strlen(token[id]))
			{
				max = ft_strlen(token[id]);
				ret = id;
			}
		id++;
	}
	if (ret != WORD)
		*i += ft_strlen(token[ret]) - 1;
	return (ret);
}

int		find_type(int *i)
{
	static int	(*f[3])(int*) = {&isblank, &isop, 0};
	int			id;
	int			ret;

	id = 0;
	ret = WORD;
	while ((*f[id]))
		if ((ret = (*f[id++])(i)) != WORD)
			return (ret);
	return (ret);
}

void	get_token(void)
{
	int	i;
	int	ret;

	i = 0;
	while (g_line[i])
	{
		ret = find_type(&i);
		printf("%c = %d\n", g_line[i], ret);
		i++;
	}
}

int		main(void)
{
	g_line = NULL;
	get_next_line(0, &g_line);
	get_token();
	return (1);
}
