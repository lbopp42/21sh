/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:22:53 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/03 15:54:21 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Function to create the token list:
**	If current char is a space and we have state, we do nothing.
**	Else
**		If the current char is an operator we create a token for it
**		Else we create a token and add the current char
**		type is type send by the last function
*/

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

/*
**	Function to add a new token to the list:
**	We malloc the next address of last token
**	If the current token is an operator we put it in the token
**	Else we create a token with the current char
**	The type is the type send by the last function
*/

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

/*
**	This function manage all the token list:
**	If we have a space and no state, we set a variable to don't forgot it
**	We add the current char in a tmp named insert
**	If we haven't token list and current char isn't a space we create it
**	Else we get the last token,
**	If current char is a space and we are not in a state we stop it now
**	Else
**		If the current token type have the same type as type send by last
**		function and new = 0 or we are in a state and new = 0
**			We add the current char to the current token
**		Else we create a new token to the end of the token list
**		And new = 0
*/

void		token_management(t_token **t_lst, t_state *s_lst, int *i, int type)
{
	char		insert[2];
	t_token		*last_tok;
	static int	new = 0;

	if ((ft_isspace(g_line[*i]) || (type >= 0 && type <= 7)) &&  !s_lst)
		new = 1;
	insert[0] = g_line[*i];
	insert[1] = '\0';
	if (!*t_lst && !ft_isspace(insert[0]))
		create_tok_lst(t_lst, s_lst, insert, type);
	else
	{
		last_tok = get_last_token(*t_lst);
		if ((ft_isspace(g_line[*i]) && !s_lst) || !last_tok)
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
