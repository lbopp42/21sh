/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:50:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/28 13:51:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	This function return WORD if it don't recognize an operator
**	Operator managed:
**	SEMICOLON = ;
**	PIPE = |
**	LESS = <
**	GREAT = >
**	DLESS = <<
**	DGREAT = >>
**	GREATAND = >&
**	LESSAND = <&
*/

int		is_new_op(int i)
{
	int			id;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	id = 0;
	while (token[id])
	{
		if (content == token[id][0])
			return (id);
		id++;
	}
	return (0);
}

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
	return (0);
}

void	add_to_current_tok(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	(*tok_lst)->content = ft_stradd((*tok_lst->content, tmp));
	(*tok_lst)->type = type;
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
	(*tok_lst)->NULL;
}

int		treatment_machine(t_token **tok_lst, int i)
{
	int	type;

	type = WORD;
	printf("[%c]\n", g_line[i]);
	if (!g_line[i])
		*tok_lst = NULL;
	else if (*tok_lst && (*tok_lst)->type >= 0 && (*tok_lst)->type <= 7
			&& (type = big_op((*tok_lst)->content, i)))
	{
		add_to_current_tok(tok_lst, i, type);
		*tok_lst = (*tok_lst)->next;
	}
	else if (*tok_lst && (*tok_lst)->type >= 0 && (*tok_lst)->type <= 7
			&& !big_op((*tok_lst)->content, i))
	{
		*tok_lst = (*tok_lst)->next;
		treatment_machine(tok_lst, i);
	}
	else if (g_line[i] == ''' || g_line[i] == '"')
	{
		/* Change the state */
		if (*tok_lst && (*tok_lst)->type == WORD)
			add_to_current_tok(tok_lst, i, WORD);
		else
			create_new_tok(tok_lst, i, type);
	}
	else if ((type = is_new_op(i)))
	{
		if (*tok_lst)
			*tok_lst = (*tok_lst)->next;
		create_new_tok(tok_lst, i, type);
	}
	if (g_line[i])
		return (1);
	else
		return (0);
}

void	lexer_posix(t_token **tok_lst)
{
	int	i;
	t_token	*first;

	first = *tok_lst;
	i = 0;
	while (treatment_machine(tok_lst, i))
		i += 1;
}

int	main(void)
{
	t_token	*tok_lst;

	g_line = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	lexer_posix(&tok_lst);
	return (1);
}
