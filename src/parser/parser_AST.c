/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_AST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:56:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/17 12:56:28 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	main(void)
{
	t_tuple	*tuple_end;
	t_token	*tok_lst;

	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->type = SEMICOLON;
	tok_lst->next->content = ft_strdup(";");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->type = GREAT;
	tok_lst->next->next->content = ft_strdup(">");
	tok_lst->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->type = WORD;
	tok_lst->next->next->next->content = ft_strdup("fifi");
	tok_lst->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->content = ft_strdup("wc");
	tok_lst->next->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->content = ft_strdup("-c");
	tok_lst->next->next->next->next->next->next = NULL;/*(t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->next->type = GREAT;
	tok_lst->next->next->next->next->next->next->content = ft_strdup(">");
	tok_lst->next->next->next->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->next->next->content = ft_strdup("fifi");
	tok_lst->next->next->next->next->next->next->next->next = NULL;*/
	tuple_end = iscomplete_cmd(tok_lst, 4, 0);
	if (tuple_end)
	{
		printf("mv final = %d\n", tuple_end->mv);
		print_AST(tuple_end->ast_tree, 0, 0);
	}
}
