/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:22:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 16:27:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

static void	create_tok_lst(t_token **t_lst, t_state *s_lst, char *ins, int type)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	if ((ft_isspace(ins[0]) && !s_lst))
		return ;
	else
	{
		if (!(*t_lst = (t_token *)ft_memalloc(sizeof(t_token))))
			return ;
		if (type >= 0 && type <= 7)
			(*t_lst)->content = ft_strdup(token[type]);
		else
			(*t_lst)->content = ft_strdup(ins);
		(*t_lst)->type = type;
		(*t_lst)->next = NULL;
	}
}

static void	add_next_token(t_token **last_tok, char *ins, int type)
{
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	if (!((*last_tok)->next = (t_token *)ft_memalloc(sizeof(t_token))))
		return ;
	if (type >= 0 && type <= 7)
		(*last_tok)->next->content = ft_strdup(token[type]);
	else
		(*last_tok)->next->content = ft_strdup(ins);
	(*last_tok)->next->type = type;
}

void		token_management(t_token **t_lst, t_state *s_lst, int *i, int type)
{
	char		insert[2];
	t_token		*last_tok;
	static int	new = 0;

	if (ft_isspace(g_line[*i]) && !s_lst)
		new = 1;
	insert[0] = g_line[*i];
	insert[1] = '\0';
	if (!*t_lst && !ft_isspace(insert[0]))
		create_tok_lst(t_lst, s_lst, insert, type);
	else
	{
		last_tok = get_last_token(*t_lst);
		if ((ft_isspace(g_line[*i]) && !s_lst))
			return ;
		else
		{
			if ((last_tok->type == type || s_lst) && !new)
				last_tok->content = ft_stradd(last_tok->content, insert);
			else
				add_next_token(&last_tok, insert, type);
			new = 0;
		}
	}
}
