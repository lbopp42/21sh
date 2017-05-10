/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_newline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 09:44:10 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/10 09:44:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	treatment_newline(t_token **tok_lst, int i, int type)
{
	if (*tok_lst)
	{
		create_new_token_next(tok_lst, i, NEWLINE);
		return (2);
	}
	else
		create_new_token(tok_lst, i, type);
	return (1);
}
