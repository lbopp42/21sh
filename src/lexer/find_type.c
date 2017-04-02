/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:40:21 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 17:01:36 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Function used to identify the type :
**	All type of quote and operator
*/

int		find_type(int *i)
{
	static int	(*f[4])(int*) = {&isop, &isquote, 0};
	int			id;
	int			ret;

	id = 0;
	ret = WORD;
	while ((*f[id]))
		if ((ret = (*f[id++])(i)) != WORD)
			return (ret);
	return (ret);
}
