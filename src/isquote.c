/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 16:36:27 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 16:36:40 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

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
