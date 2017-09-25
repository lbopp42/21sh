/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_of_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 09:34:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/25 13:00:13 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	treatment_of_new_word(t_token **tok_lst, int *sp, int i)
{
	if (*sp && *tok_lst)
	{
		*sp = 0;
		create_new_token_next(tok_lst, i, WORD);
		return (2);
	}
	else
	{
		*sp = 0;
		create_new_token(tok_lst, i, WORD);
	}
	return (1);
}

int	treatment_of_old_word(t_token **tok_lst, int *sp, int i)
{
	*sp = 0;
	add_to_current_tok(tok_lst, i, WORD);
	return (1);
}
