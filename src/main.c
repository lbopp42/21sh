/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:02:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/26 16:42:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		isblank(int *i)
{
	if (ft_isspace(g_line[*i]))
		return (BLANK);
	return (WORD);
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

int		find_type(int *i)
{
	static int	(*f[4])(int*) = {&isblank, &isop, &isquote, 0};
	int			id;
	int			ret;

	id = 0;
	ret = WORD;
	while ((*f[id]))
		if ((ret = (*f[id++])(i)) != WORD)
			return (ret);
	return (ret);
}

void	state_management(t_state **state_lst, int type)
{
	t_state	*tmp;
	t_state	*first;

	first = NULL;
	tmp = *state_lst;
	if (!*state_lst)
	{
		if (!(*state_lst = (t_state*)ft_memalloc(sizeof(t_state))))
			return ;
		(*state_lst)->state = type;
		(*state_lst)->next = NULL;
	}
	else
	{
		if ((*state_lst)->state == type && !(*state_lst)->next)
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
		if (tmp->state == type)
		{
			free(tmp);
			tmp = NULL;
			if (first && first->next)
				first->next = NULL;
		}
		else
		{
			if (!(tmp->next = (t_state*)ft_memalloc(sizeof(t_state))))
				return ;
			tmp->next->state = type;
			tmp->next->next = NULL;
		}
	}
}

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

void	token_management(t_token **tok_lst, int type, t_state *state_lst, int *i)
{
	char		*tmp;
	t_token		*tmp_tok;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	while (state_lst && state_lst->next)
		state_lst = state_lst->next;
	tmp = NULL;
	tmp = ft_strsub((const char*)g_line, *i, 1);
	if (!*tok_lst)
	{
		if (!(*tok_lst = (t_token*)ft_memalloc(sizeof(t_token))))
			return ;
		(*tok_lst)->content = ft_strdup(tmp);
		(*tok_lst)->type = type;
		(*tok_lst)->next = NULL;
	}
	else
	{
		tmp_tok = *tok_lst;
		while (tmp_tok->next)
			tmp_tok = tmp_tok->next;
		if ((tmp_tok->type == type || state_lst) && g_line[*i] != '`' &&
				g_line[*i] != '\'' && g_line[*i] != '\"' &&
				ft_strcmp(tmp_tok->content, "\""))
			tmp_tok->content = ft_stradd(tmp_tok->content, tmp);
		else
		{
			if (!(tmp_tok->next = (t_token*)ft_memalloc(sizeof(t_token))))
				return ;
			if (type >= 0 && type <= 7)
				tmp_tok->next->content = ft_strdup(token[type]);
			else
				tmp_tok->next->content = ft_strdup(tmp);
			/*if (state_lst)
			{
				tmp_tok->next->type = state_lst->state;
				printf("[%c]\n", g_line[*i]);
			}
			else*/
				tmp_tok->next->type = type;
			tmp_tok->next->next = NULL;
		}
	}
}

void	get_token(t_token **tok_lst)
{
	int		i;
	int		ret;
	t_state	*state_lst;

	i = 0;
	state_lst = NULL;
	while (g_line[i])
	{
		ret = find_type(&i);
		if (ret == QUOTE || ret == DQUOTE || ret == BQUOTE)
			state_management(&state_lst, ret);
		token_management(tok_lst, ret, state_lst, &i);
		i++;
	}
}

int		main(void)
{
	t_token	*tok_lst;

	g_line = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	get_token(&tok_lst);
	print_lst(tok_lst);
	return (1);
}
