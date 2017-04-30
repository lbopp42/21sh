/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 10:07:05 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/30 16:57:53 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		big_op(char *content, int i)
{
	char		tmp[3];
	int			curs;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	curs = 0;
	tmp[0] = content[0];
	tmp[1] = g_line[i];
	tmp[2] = '\0';
	while (token[curs])
	{
		if (ft_strequ((const char*)tmp, (const char*)token[curs]))
			return (curs);
		curs += 1;
	}
	return (WORD);
}

void	state_management(t_state **st_lst, int i)
{
	t_state	*tmp;
	t_state	*first;

	if (!*st_lst)
	{
		if (!(*st_lst = (t_state*)ft_memalloc(sizeof(t_state))))
			return ;
		if (g_line[i] == '"')
			(*st_lst)->state = DQUOTE;
		else
			(*st_lst)->state = QUOTE;
		(*st_lst)->next = NULL;
	}
	else
	{
		tmp = *st_lst;
		while (tmp->next)
		{
			first = tmp;
			tmp = tmp->next;
		}
		if (g_line[i] == '"' && tmp->state == DQUOTE)
		{
			if (!(*st_lst)->next)
			{
				free(*st_lst);
				*st_lst = NULL;
				return ;
			}
			free(tmp);
			first->next = NULL;
			tmp = NULL;
		}
		else if (g_line[i] == '\'' && tmp->state == QUOTE)
		{
			if (!(*st_lst)->next)
			{
				free(*st_lst);
				*st_lst = NULL;
				return ;
			}
			free(tmp);
			first->next = NULL;
			tmp = NULL;
		}
		else
		{
			if (!(tmp->next = (t_state*)ft_memalloc(sizeof(t_state))))
				return ;
			if (g_line[i] == '"')
				tmp->next->state = DQUOTE;
			else
				tmp->next->state = QUOTE;
			tmp->next = NULL;
		}
	}
}

void	add_to_current_tok(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	(*tok_lst)->content = ft_stradd((*tok_lst)->content, tmp);
	(*tok_lst)->type = type;
}

void	create_new_token_next(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	if (!((*tok_lst)->next = (t_token*)ft_memalloc(sizeof(t_token))))
		return ;
	(*tok_lst)->next->type = type;
	(*tok_lst)->next->content = ft_strdup(tmp);
	(*tok_lst)->next->next = NULL;
}

void	create_new_token(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	if (!(*tok_lst = (t_token*)ft_memalloc(sizeof(t_token))))
		return ;
	(*tok_lst)->type = type;
	(*tok_lst)->content = ft_strdup(tmp);
	(*tok_lst)->next = NULL;
}

int		is_new_op(int i)
{
	int			id;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	id = 0;
	while (token[id])
	{
		if (g_line[i] == token[id][0])
			return (id);
		id++;
	}
	return (WORD);
}

int	treatment_char(t_token **tok_lst, t_state **st_lst, int i)
{
	int			tmp;
	static int	sp = 0;

	if (!g_line[i])
	{
		if (*tok_lst)
			(*tok_lst)->next = NULL;
		return (0);
	}
	else if (!sp && *tok_lst && (*tok_lst)->type >= SEMICOLON &&
			(*tok_lst)->type <= LESSAND &&
			(tmp = big_op((*tok_lst)->content, i)) != WORD && !*st_lst)
	{
		sp = 0;
		add_to_current_tok(tok_lst, i, tmp);
		return (1);
	}
	else if (*tok_lst && (*tok_lst)->type >= SEMICOLON &&
			(*tok_lst)->type <= LESSAND &&
			big_op((*tok_lst)->content, i) == WORD && !*st_lst)
	{
		if (g_line[i] != ' ' && g_line[i] != '\t')
		{
			create_new_token_next(tok_lst, i, WORD);
			return (2);
		}
		sp = 0;
		return (1);
	}
	else if (g_line[i] == '"' || g_line[i] == '\'')
	{
		state_management(st_lst, i);
		if (*tok_lst && !sp && (*tok_lst)->type == WORD)
		{
			sp = 0;
			add_to_current_tok(tok_lst, i, WORD);
			return (1);
		}
		else if (*tok_lst)
		{
			create_new_token_next(tok_lst, i, WORD);
			return (2);
		}
		else
		{
			create_new_token(tok_lst, i, WORD);
			return (1);
		}
	}
	else if ((tmp = is_new_op(i)) != WORD && !*st_lst)
	{
		sp = 0;
		if (*tok_lst)
		{
			create_new_token_next(tok_lst, i, tmp);
			return (2);
		}
		else
		{
			create_new_token(tok_lst, i, tmp);
			return (1);
		}
	}
	else if (g_line[i] == '\n' && !*st_lst)
	{
		if (*tok_lst)
		{
			create_new_token_next(tok_lst, i, NEWLINE);
			return (2);
		}
		else
		{
			create_new_token(tok_lst, i, tmp);
			return (1);
		}
	}
	else if (!*st_lst && (g_line[i] == ' ' || g_line[i] == '\t'))
	{
		sp = 1;
		return (1);
	}
	else if (*tok_lst && (*tok_lst)->type == WORD && !sp)
	{
		sp = 0;
		add_to_current_tok(tok_lst, i, WORD);
	}
	else
	{
		if (sp)
		{
			sp = 0;
			create_new_token_next(tok_lst, i, WORD);
			return (2);
		}
		else
			create_new_token(tok_lst, i, WORD);
	}
	return (1);
}

void	lexer_posix(t_token **tok_lst, t_state **st_lst)
{
	int	i;
	static int test = 0;
	int	tmp;
	t_token	*first;

	i = 0;
	while (1)
	{
		tmp = treatment_char(tok_lst, st_lst, i);
		if (*tok_lst && !test)
		{
			first = *tok_lst;
			test += 1;
		}
		if (tmp == 1)
		{
			i += 1;
		}
		else if (tmp == 2)
		{
			*tok_lst = (*tok_lst)->next;
			i += 1;
		}
		else
			break ;
	}
	*tok_lst = first;
}

int	main(void)
{
	t_token	*tok_lst;
	t_state	*st_lst;

	st_lst = NULL;
	g_line = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	lexer_posix(&tok_lst, &st_lst);
	printf("===============================================\n");
	while (tok_lst)
	{
		printf("[%s] ; [%d]\n", tok_lst->content, tok_lst->type);
		tok_lst = tok_lst->next;
	}
	return (1);
}
