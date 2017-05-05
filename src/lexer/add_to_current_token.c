/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_current_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:30:40 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 12:31:17 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	add_to_current_tok(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	(*tok_lst)->content = ft_stradd((*tok_lst)->content, tmp);
	(*tok_lst)->type = type;
}
