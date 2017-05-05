/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 13:40:54 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 13:41:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

static void	pop_current_state(t_state **st_lst, t_state **first, t_state **tmp)
{
	if (!(*st_lst)->next)
	{
		free(*st_lst);
		*st_lst = NULL;
		return ;
	}
	free(*tmp);
	(*first)->next = NULL;
	*tmp = NULL;
}

static void	create_new_state(t_state **st_lst, int i)
{
	if (!(*st_lst = (t_state*)ft_memalloc(sizeof(t_state))))
		return ;
	if (g_line[i] == '"')
		(*st_lst)->state = DQUOTE;
	else
		(*st_lst)->state = QUOTE;
	(*st_lst)->next = NULL;
}

void		state_management(t_state **st_lst, int i)
{
	t_state	*tmp;
	t_state	*first;

	if (!*st_lst)
		create_new_state(st_lst, i);
	else
	{
		tmp = *st_lst;
		while (tmp->next)
		{
			first = tmp;
			tmp = tmp->next;
		}
		if (g_line[i] == '"' && tmp->state == DQUOTE)
			pop_current_state(st_lst, &first, &tmp);
		else if (g_line[i] == '\'' && tmp->state == QUOTE)
			pop_current_state(st_lst, &first, &tmp);
		else
			create_new_state(&tmp->next, i);
	}
}
