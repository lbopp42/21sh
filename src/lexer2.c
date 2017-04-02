/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:24:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 12:07:18 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	print_lst(t_token *tok_lst)
{
	t_token	*tmp;
	/*char	*test[] = {"SEMICOLON", "PIPE", "LESS", "DLESS", "GREAT", "DGREAT",
	  "INPUT", "OUTPUT", "WORD", "BLANK"};*/

	tmp = tok_lst;
	while (tmp)
	{
		printf("TOKEN = [%s] and TYPE = %d\n", tmp->content, tmp->type);
		tmp = tmp->next;
	}
}

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

int		isquote(int *i)
{
	if (g_line[*i] == '"')
		return (DQUOTE);
	else if (g_line[*i] == '\'')
		return (QUOTE);
	else if (g_line[*i] == '`')
		return (BQUOTE);
	else
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

	last = NULL;
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

void	state_management(t_state **state_lst, int *i)
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

t_token	*get_last_token(t_token *tok_lst)
{
	t_token	*last;

	last = tok_lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	token_management(t_token **tok_lst, t_state *st_lst, int *i, int type)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};
	char		insert[2];
	t_token		*last_tok;
	static int	new = 0;

	if (ft_isspace(g_line[*i]))
		new = 1;
	insert[0] = g_line[*i];
	insert[1] = '\0';
	if (!*tok_lst && !ft_isspace(insert[0]))
	{
		if (!(*tok_lst = (t_token *)ft_memalloc(sizeof(t_token))))
			return ;
		if (type >= 0 && type <= 7)
			(*tok_lst)->content = ft_strdup(token[type]);
		else
			(*tok_lst)->content = ft_strdup(insert);
		(*tok_lst)->type = type;
		(*tok_lst)->next = NULL;
	}
	else if (!ft_isspace(insert[0]))
	{
		last_tok = get_last_token(*tok_lst);
		if ((last_tok->type == type || st_lst) && !new)
			last_tok->content = ft_stradd(last_tok->content, insert);
		else
		{
			if (!(last_tok->next = (t_token *)ft_memalloc(sizeof(t_token))))
				return ;
			if (type >= 0 && type <= 7)
				last_tok->next->content = ft_strdup(token[type]);
			else
				last_tok->next->content = ft_strdup(insert);
			last_tok->next->type = type;
		}
		new = 0;
	}
}

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

void	treat_char(int *i, t_token **tok_lst, t_state **state_lst)
{
	int	type;

	if (isquote(i) != WORD)
		state_management(state_lst, i);
	if (get_last_state(*state_lst) == NULL)
		type = find_type(i);
	else
		type = get_last_state(*state_lst)->state;
	//printf("ON PASSE\n");
	if (isquote(i) == WORD)
		token_management(tok_lst, *state_lst, i, type);
}

void	fill_tok_lst(t_token **tok_lst, t_state **state_lst)
{
	int	i;

	i = 0;
	while (g_line[i])
	{
		treat_char(&i, tok_lst, state_lst);
		i++;
	}
}
