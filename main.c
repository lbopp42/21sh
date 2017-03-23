/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:02:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/23 17:25:49 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	add_tok(char *add, char **current_tok)
{
	if (!*current_tok)
		*current_tok = ft_strdup(add);
	else
		*current_tok = ft_stradd(*current_tok, add);
}

void	put_in_lst(char *curr_tok, t_token **token_lst, int type)
{
	t_token	*tmp;

	if (!*token_lst)
	{
		if (!(*token_lst = (t_token*)ft_memalloc(sizeof(t_token))))
			return ;
		(*token_lst)->type = type;
		(*token_lst)->content = ft_strdup(curr_tok);
		(*token_lst)->next = NULL;
	}
	else
	{
		tmp = *token_lst;
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_token*)ft_memalloc(sizeof(t_token))))
			return ;
		tmp->next->type = type;
		tmp->next->content = ft_strdup(curr_tok);
		tmp->next->next = NULL;
	}
}

void	func_space_tok(char **curr_tok, t_token **token_lst, int *type, int *i)
{
	if (*curr_tok)
	{
		put_in_lst(*curr_tok, token_lst, *type);
		ft_strdel(curr_tok);
	}
	while (ft_isspace(g_line[*i]))
		*i += 1;
	*i -= 1;
	put_in_lst(" ", token_lst, BLANK);
}

void	print_lst(t_token *tok_array)
{
	while (tok_array)
	{
		printf("TYPE = %d et TOKEN = %s\n", tok_array->type, tok_array->content);
		tok_array = tok_array->next;
	}
}

int		token_in_array(int *i)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};
	int			id;
	int			ret;
	size_t		max;

	id = 0;
	ret = -1;
	max = 0;
	while (token[id])
	{
		if (!ft_strncmp(&(g_line[*i]), token[id], ft_strlen(token[id])))
		{
			max = max < ft_strlen(token[id]) ? ft_strlen(token[id]) : max;
			ret = id;
		}
		id++;
	}
	if (ret != -1)
		*i += max - 1;
	return (ret);
}

void	func_op_tok(char **curr_tok, t_token **token_lst, int type, int ret)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	if (*curr_tok)
		put_in_lst(*curr_tok, token_lst, type);
	ft_strdel(curr_tok);
	put_in_lst((char*)token[ret], token_lst, ret);
}

void	get_token(void)
{
	char	*curr_tok;
	char	*tmp;
	int		i;
	int		type;
	t_token	*token_lst;
	int		ret;

	i = 0;
	tmp = NULL;
	ret = -1;
	type = -1;
	curr_tok = NULL;
	token_lst = NULL;
	while (g_line[i])
	{
		if (ft_isspace(g_line[i]))
			func_space_tok(&curr_tok, &token_lst, &type, &i);
		else if ((ret = token_in_array(&i)) >= 0)
			func_op_tok(&curr_tok, &token_lst, type, ret);
		else
		{
			tmp = ft_strsub(g_line, i, 1);
			add_tok(tmp, &curr_tok);
			type = WORD;
		}
		i++;
		ft_strdel(&tmp);
	}
	if (curr_tok)
		put_in_lst(curr_tok, &token_lst, type);
	print_lst(token_lst);
}

int		main(void)
{
	g_line = NULL;
	get_next_line(0, &g_line);
	get_token();
	return (1);
}
