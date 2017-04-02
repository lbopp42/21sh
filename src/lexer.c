/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:24:52 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 16:43:53 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	treat_char(int *i, t_token **tok_lst, t_state **state_lst)
{
	int	type;

	if (isquote(i) != WORD)
		state_management(state_lst, i);
	if (get_last_state(*state_lst) == NULL)
		type = find_type(i);
	else
		type = get_last_state(*state_lst)->state;
	if (isquote(i) == WORD || (*state_lst && (*state_lst)->state != isquote(i)))
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
