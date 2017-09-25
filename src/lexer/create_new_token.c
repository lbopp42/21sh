/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:23:42 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/25 13:03:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	create_new_token_next(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	if (!((*tok_lst)->next = (t_token*)ft_memalloc(sizeof(t_token))))
		return ;
	(*tok_lst)->next->type = type;
	(*tok_lst)->next->content = ft_strdup(tmp);
	(*tok_lst)->next->next = NULL;
}

void	create_new_token(t_token **tok_lst, int i, int type)
{
	char	tmp[2];

	tmp[0] = g_line[i];
	tmp[1] = '\0';
	if (!(*tok_lst = (t_token*)ft_memalloc(sizeof(t_token))))
		return ;
	(*tok_lst)->type = type;
	(*tok_lst)->content = ft_strdup(tmp);
	(*tok_lst)->next = NULL;
}
