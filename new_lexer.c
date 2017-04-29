/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 12:50:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/29 11:47:35 by lbopp            ###   ########.fr       */
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
		if (g_line[i] == token[id][0])
			return (id);
		id++;
	}
	return (WORD);
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
	(*tok_lst)->content = ft_stradd((*tok_lst)->content, tmp);
	(*tok_lst)->type = type;
}

t_token	*create_new_token(t_token *tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	if (!(tok_lst = (t_token*)ft_memalloc(sizeof(t_token))))
		return (NULL);
	tok_lst->type = type;
	tok_lst->content = ft_strdup(tmp);
	return (tok_lst);
}

int		treatment_machine(t_token **tok_lst, int i)
{
	int	type;

	type = WORD;
	printf("On traite [%c]\n", g_line[i]);
	if (!g_line[i])
	{
		*tok_lst = NULL;
		return (0);
	}
	else if (*tok_lst && (*tok_lst)->type >= 0 && (*tok_lst)->type <= 7
			&& (type = big_op((*tok_lst)->content, i)))
	{
		add_to_current_tok(tok_lst, i, type);
	}
	else if (*tok_lst && (*tok_lst)->type >= 0 && (*tok_lst)->type <= 7
			&& !big_op((*tok_lst)->content, i))
	{
		printf("i = %d, et [%c]\n", i, g_line[i]);
		if (g_line[i] == ' ' || g_line[i] == '\n')
			return (2);
		else
			return (1);
	}
	else if (g_line[i] == '\'' || g_line[i] == '"')
	{
		/* Change the state */
		if (*tok_lst && (*tok_lst)->type == WORD)
			add_to_current_tok(tok_lst, i, WORD);
		else
			*tok_lst = create_new_token(*tok_lst, i, type);
	}
	else if ((type = is_new_op(i)) != WORD)
	{
		if (*tok_lst)
			return (1);
		*tok_lst = create_new_token(*tok_lst, i, type);
	}
	else if (g_line[i] == '\n')
	{
		if (*tok_lst)
			return (1);
		*tok_lst = create_new_token(*tok_lst, i, NEWLINE);
	}
	else if (g_line[i] == ' ' || g_line[i] == '\t')
	{
		if (*tok_lst)
			return (2);
	}
	else if (*tok_lst && (*tok_lst)->type == WORD)
	{
		printf("On passe ici pour [%c]\n", g_line[i]);
		add_to_current_tok(tok_lst, i, WORD);
	}
	else
	{
		printf("On creer un maillon WORD pour [%c]\n", g_line[i]);
		*tok_lst = create_new_token(*tok_lst, i, WORD);
	}
	return (3);
}

/*
**	Actually need a strtrim before run this function.
*/

void	lexer_posix(t_token **tok_lst)
{
	int	i;
	int	tmp;
	t_token	*first;

	first = *tok_lst;
	i = 0;
	tmp = treatment_machine(tok_lst, i);
	first = *tok_lst;
	while (1)
	{
		if (tmp == 2)
		{
			i += 1;
			tmp = treatment_machine(&(*tok_lst)->next, i);
			*tok_lst = (*tok_lst)->next;
		}
		else if (tmp == 1)
		{
			tmp = treatment_machine(&(*tok_lst)->next, i);
			*tok_lst = (*tok_lst)->next;
		}
		else if (tmp)
		{
			i += 1;
			tmp = treatment_machine(tok_lst, i);
		}
		else
			break;
	}
	while (first)
	{
		printf("IN LIST [%s] DE TYPE [%d]\n", first->content, first->type);
		first = first->next;
	}
}

int	main(void)
{
	t_token	*tok_lst;

	g_line = NULL;
	tok_lst = NULL;
	get_next_line(0, &g_line);
	lexer_posix(&tok_lst);
	printf("===============================================\n");
	while (tok_lst)
	{
		printf("[%s] ; [%d]\n", tok_lst->content, tok_lst->type);
		tok_lst = tok_lst->next;
	}
	return (1);
}
