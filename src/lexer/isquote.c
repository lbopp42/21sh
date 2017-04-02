/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:36:27 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 17:09:24 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*
**	This function return an int which corresponds to a quote
**	or
**	WORD if it's not a quote
**	Quote managed : BQUOTE = `
**					DQUOTE = "
**					QUOTE = '
*/

int		isquote(int *i)
{
	if (g_line[*i] == '"')
		return (DQUOTE);
	else if (g_line[*i] == '\'')
		return (QUOTE);
	else if (g_line[*i] == '`')
		return (BQUOTE);
	else
		return (WORD);
}
