/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 13:08:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 13:37:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

static void	fill_lst(t_list *lst, char ***array)
{
	int		i;
	int		k;
	t_list	*origin;

	origin = lst;
	i = 0;
	while (origin)
	{
		k = 0;
		while (((char*)origin->content)[k])
		{
			(*array)[i][k] = ((char*)origin->content)[k];
			k++;
		}
		i++;
		origin = origin->next;
	}
}

static void	create_line(t_list *lst, char ***array)
{
	int		size;
	int		i;
	t_list	*origin;

	i = 0;
	origin = lst;
	while (lst != NULL)
	{
		size = ft_strlen(lst->content) + 1;
		if (!((*array)[i] = (char*)ft_memalloc(size + 1)))
			return ;
		i++;
		lst = lst->next;
	}
	lst = origin;
}

static int	lst_size(t_list *lst)
{
	int		size;
	t_list	*origin;

	origin = lst;
	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	lst = origin;
	return (size);
}

char	**list_to_array(t_list *lst)
{
	char	**array;
	int		size;
	t_list	*origin;

	origin = lst;
	array = NULL;
	size = lst_size(lst);
	if (!(array = (char**)ft_memalloc(sizeof(char*) * (size + 1))))
		return (NULL);
	create_line(lst, &array);
	lst = origin;
	fill_lst(lst, &array);
	return (array);
}
