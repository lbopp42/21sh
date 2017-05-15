/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_AST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 10:42:39 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/15 10:47:10 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

t_ast_node	*create_ast_node(t_token *tok_root, t_token *tok_left, t_token *tok_right)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
	new_node->type = tok_root->type;
	new_node->content = ft_strdup(tok_root->content);
	if (tok_left)
	{
		new_node->left = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->left->type = tok_left->type;
		new_node->left->content = ft_strdup(tok_left->content);
		new_node->left->left = NULL;
		new_node->left->right = NULL;
	}
	else
		new_node->left = NULL;
	if (tok_right)
	{
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = tok_right->type;
		new_node->right->content = ft_strdup(tok_right->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
	}
	else
		new_node->right = NULL;
	return (new_node);
}

t_tuple	*isio_file(t_token *tok_lst, t_tuple *last_tpl)
{
	t_tuple	*tmp;

	tmp = last_tpl;
	while (tmp && tmp->mv > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		
	}
}
