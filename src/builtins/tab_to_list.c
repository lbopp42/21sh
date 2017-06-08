/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:39:49 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 10:51:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	create_lst(t_lst **lst, char *array)
{
	if (!(*lst = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	(*lst)->name = ft_strcdup(array, '=');
	(*lst)->content = ft_strdup(ft_strchr(array, '=') + 1);
	(*lst)->next = NULL;
}

void	add_lst(t_lst **lst, char *array)
{
	if (*lst == NULL)
		create_lst(lst, array);
	else
		add_lst(&((*lst)->next), array);
}

t_lst	*tab_to_list(char *array[])
{
	int		i;
	t_lst	*lst;

	lst = NULL;
	i = 0;
	while (array[i])
	{
		add_lst(&lst, array[i]);
		i++;
	}
	return (lst);
}

void	del_lst(t_lst *lst)
{
	if (!lst)
		return ;
	if (lst->next != NULL)
		del_lst(lst->next);
	free(lst->content);
	free(lst->name);
	free(lst);
}
