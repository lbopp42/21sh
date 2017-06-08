/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 10:51:28 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	fill_lst(t_lst *lst, char ***array)
{
	int		i;
	int		j;
	int		k;
	t_lst	*origin;

	origin = lst;
	i = 0;
	while (origin)
	{
		j = 0;
		k = 0;
		while (origin->name[j])
		{
			(*array)[i][j] = origin->name[j];
			j++;
		}
		(*array)[i][j] = '=';
		while (origin->content[k])
		{
			(*array)[i][j + 1 + k] = origin->content[k];
			k++;
		}
		i++;
		origin = origin->next;
	}
}

void	create_line(t_lst *lst, char ***array)
{
	int		size;
	int		i;
	t_lst	*origin;

	i = 0;
	origin = lst;
	while (lst != NULL)
	{
		size = ft_strlen(lst->name) + ft_strlen(lst->content) + 1;
		if (!((*array)[i] = (char*)ft_memalloc(size + 1)))
			return ;
		i++;
		lst = lst->next;
	}
	lst = origin;
}

int		lst_size(t_lst *lst)
{
	int		size;
	t_lst	*origin;

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

char	**list_to_tab(t_lst *lst)
{
	char	**array;
	int		size;
	t_lst	*origin;

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

void	del_array(char *array[])
{
	int i;

	i = 0;
	if (!array || !array[0])
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}
