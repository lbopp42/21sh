/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:24:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/28 12:49:57 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	Operation of treat_char:
**		If we have a quote, we treat it on state_management function
**		If we haven't state, we try to find the type on find_type function
**		Else the type will be the current state (last in state_lst)
**		And to finish if we have a WORD or a quote but different
**		from the current state we treat it with token_management
*/

void	treat_char(int *i, t_token **tok_lst, t_state **state_lst)
{
	int	type;

	if (isquote(i) != WORD)
		state_management(state_lst, i);
	if (get_last_state(*state_lst) == NULL)
		type = isop(i);
	else
		type = WORD;//get_last_state(*state_lst)->state;
	//if (isquote(i) == WORD || (*state_lst && (*state_lst)->state != isquote(i))*/)
		token_management(tok_lst, *state_lst, i, type);
}

/*
**	fill_tok_lst will treat each char
*/

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
