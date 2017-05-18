/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_AST.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 12:56:00 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/18 12:26:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	print_AST(t_ast_node *ast_tree, int mode, int layer)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		print_AST(ast_tree->left, 1, layer + 1);
	if (ast_tree->right)
		print_AST(ast_tree->right, 2, layer + 1);
	if (mode == 1)
		printf("LEFT = [%s], LAYER = %d\n", ast_tree->content, layer);
	else if (mode == 2)
		printf("RIGHT = [%s], LAYER = %d\n", ast_tree->content, layer);
	else
		printf("ROOT = [%s], LAYER = %d\n", ast_tree->content, layer);
}

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

t_tuple	*isio_file(t_token *tok_lst, int nb_tok, t_tuple *last)
{
	int			tmp;
	int			mv;
	t_tuple		*tuple_parse;

	mv = 0;
	if (last)
		mv = last->mv;
	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	(void)nb_tok;
	if (tok_lst->type == LESS && tok_lst->next && tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == LESSAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREATAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == DGREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	return (NULL);
}

t_tuple	*isio_number(t_token *tok_lst, int nb_tok, int mv)
{
	int		tmp;
	t_tuple	*tuple_parse;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if (tok_lst->type == IO_NUMBER)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		tuple_parse->mv = mv + 1;
		return (tuple_parse);
	}
	return (NULL);
}

t_tuple	*isio_redirect(t_token *tok_lst, int nb_tok, t_tuple *last)
{
	int			tmp;
	int			mv;
	t_tuple		*tuple_parse;

	mv = 0;
	if (last)
		mv = last->mv;
	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if ((tuple_parse = isio_file(tok_lst, nb_tok, NULL)))
		return (tuple_parse);
	else if ((tuple_parse = isio_number(tok_lst, nb_tok, last->mv)) &&
			(tuple_parse = isio_file(tok_lst, nb_tok, tuple_parse)))
		return (tuple_parse);
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		if (last)
			tuple_parse->ast_tree =
				create_ast_node(tok-lst, last->ast_tree, tok_lst->next);
		else
			tuple_parse->ast_tree =
				create_ast_node(tok-lst, NULL, tok_lst->next);
		tuple_parse->mv = mv + 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->ast_tree =
			create_ast_node(tok_lst->next, tok_lst, tok_lst->next->next);
		tuple_parse->mv = mv + 3;
		return (tuple_parse);
	}
	return (NULL);
}

t_tuple	*is_word(t_token *tok_lst, int mv)
{
	int		tmp;
	t_tuple	*tuple_parse;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if (tok_lst->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 1;
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		return (tuple_parse);
	}
	else
		return (NULL);
}

t_tuple	*iscmd_prefix(t_token *tok_lst, int nb_tok, t_tuple *last)
{
	int		tmp;
	t_tuple	*tuple_parse;
	t_tuple	*max_tuple;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	max_tuple = NULL;
	tuple_parse = NULL;
	tmp = mv;
	if ((tuple_parse = isio_redirect(tok_lst, nb_tok, 0)) || (tuple_parse = is_word(tok_lst, 0)))
	{
		max_tuple = tuple_parse;
		//printf("================\n");
		//print_AST(max_tuple->ast_tree, 0, 0);
		while ((tuple_parse = isio_redirect(tok_lst, nb_tok, max_tuple->mv)) ||
				(tuple_parse = is_word(tok_lst, max_tuple->mv)))
		{
			if (max_tuple->ast_tree->type == WORD && tuple_parse->ast_tree->type == WORD)
			{
				max_tuple->ast_tree->content = ft_stradd(max_tuple->ast_tree->content, " ");
				max_tuple->ast_tree->content =
					ft_stradd(max_tuple->ast_tree->content, tuple_parse->ast_tree->content);
			}
			else if (!max_tuple->ast_tree->left && tuple_parse->ast_tree->type == WORD)
			{
				max_tuple->ast_tree->left = tuple_parse->ast_tree;
			}
			else if (max_tuple->ast_tree->left && max_tuple->ast_tree->left->type == WORD
					&& tuple_parse->ast_tree->type == WORD && !max_tuple->ast_tree->right)
			{
				//printf("IL ENTRE LA\n");
				max_tuple->ast_tree->left->content = ft_stradd(max_tuple->ast_tree->left->content, " ");
				max_tuple->ast_tree->left->content =
					ft_stradd(max_tuple->ast_tree->left->content, tuple_parse->ast_tree->content);
			}
			else if (max_tuple->ast_tree->right && max_tuple->ast_tree->right->type == WORD &&
					tuple_parse->ast_tree->type == WORD)
			{
				max_tuple->ast_tree->right->content = ft_stradd(max_tuple->ast_tree->right->content, " ");
				max_tuple->ast_tree->right->content =
					ft_stradd(max_tuple->ast_tree->right->content, tuple_parse->ast_tree->content);
			}
			else
			{
				tuple_parse->ast_tree->left = max_tuple->ast_tree;
				max_tuple = tuple_parse;
			}
			max_tuple->mv = tuple_parse->mv;
		//printf("================\n");
		//print_AST(max_tuple->ast_tree, 0, 0);
		}
	}
	return (max_tuple);
}

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
