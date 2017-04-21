/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:37:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/21 11:16:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	This function return WORD if it don't recognize an operator
**	Operator managed:
**	SEMICOLON = ;
**	PIPE = |
**	LESS = <
**	GREAT = >
**	DLESS = <<
**	DGREAT = >>
**	GREATAND = >&
**	LESSAND = <&
*/

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
