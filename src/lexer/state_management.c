/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:30:42 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 17:28:30 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Function to create a simple state_lst
*/

static void	create_state(t_state **state_lst, int state)
{
	if (!(*state_lst = (t_state *)ft_memalloc(sizeof(t_state))))
		return ;
	(*state_lst)->state = state;
	(*state_lst)->next = NULL;
}

/*
**	Function to pop the current state (the last state on the list)
*/

static void	pop_state(t_state **state_lst)
{
	t_state	*tmp;
	t_state	*first;

	tmp = *state_lst;
	if (!((*state_lst)->next))
	{
		free(*state_lst);
		*state_lst = NULL;
		return ;
	}
	while (tmp->next)
	{
		first = tmp;
		tmp = tmp->next;
	}
	free(tmp);
	first->next = NULL;
	tmp = NULL;
}

/*
**	Function to push a new state:
**	We go to the last state of the list and we add one after it
*/

static void	push_state(t_state **state_lst, int state)
{
	t_state	*tmp;

	tmp = *state_lst;
	while (tmp->next)
		tmp = tmp->next;
	if (!(tmp->next = (t_state*)ft_memalloc(sizeof(t_state))))
		return ;
	tmp->next->state = state;
	tmp->next->next = NULL;
}

/*
**	Function to manage the state:
**	If we haven't state, we create if with create_state function
**	Else if the current state is QUOTE (a simple quote),
**		If we have again a QUOTE we pop it with pop_state else we do nothing
**	Else
**		If the current state (last of the state_lst) is a quote, we pop it
**		Else we push it on the state_lst
*/

void		state_management(t_state **state_lst, int *i)
{
	if (!*state_lst)
		create_state(state_lst, isquote(i));
	else if ((*state_lst)->state == QUOTE)
	{
		if (isquote(i) == QUOTE)
			pop_state(state_lst);
	}
	else
	{
		if (get_last_state(*state_lst)->state == isquote(i))
			pop_state(state_lst);
		else
			push_state(state_lst, isquote(i));
	}
}
