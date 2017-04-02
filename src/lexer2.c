/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:24:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 10:52:50 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	print_state_lst(t_state *state_lst)
{
	t_state	*tmp;

	tmp = state_lst;
	while (tmp)
	{
		printf("In state_list : %d\n", tmp->state);
		tmp = tmp->next;
	}
}

int		isquote(int i)
{
	if (g_line[i] == '"')
		return (DQUOTE);
	else if (g_line[i] == '\'')
		return (QUOTE);
	else if (g_line[i] == '`')
		return (BQUOTE);
	else
		return (0);
}

void	create_state(t_state **state_lst, int state)
{
	if (!(*state_lst = (t_state *)ft_memalloc(sizeof(t_state))))
		return ;
	(*state_lst)->state = state;
	(*state_lst)->next = NULL;
}

t_state	*get_last_state(t_state *state_lst)
{
	t_state	*last;

	while (state_lst)
	{
		last = state_lst;
		state_lst = state_lst->next;
	}
	return (last);
}

void	pop_state(t_state **state_lst)
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

void	push_state(t_state **state_lst, int state)
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

void	state_management(t_state **state_lst, int i)
{
	if (!*state_lst)
		create_state(state_lst, isquote(i));
	else if ((*state_lst)->state == QUOTE)
	{
		if (isquote(i) == QUOTE)
			pop_state(state_lst);
	}
	else
		if (get_last_state(*state_lst)->state == isquote(i))
			pop_state(state_lst);
		else
			push_state(state_lst, isquote(i));
}

void	treat_char(int *i, t_token **tok_lst, t_state **state_lst)
{
	(void)tok_lst;
	if (isquote(*i))
		state_management(state_lst, *i);
}

void	fill_tok_lst(t_token **tok_lst, t_state **state_lst)
{
	int	i;

	i = 0;
	while (g_line[i])
	{
		if (!ft_isspace(g_line[i]))
			treat_char(&i, tok_lst, state_lst);
		i++;
	}
}
