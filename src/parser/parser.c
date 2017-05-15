/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:32:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/15 15:14:31 by lbopp            ###   ########.fr       */
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

t_tuple	*isio_file(t_token *tok_lst, int nb_tok, int mv)
{
	int			tmp;
	t_ast_node	*new_node;
	t_tuple		*tuple_parse;

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
		new_node = create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = new_node;
		return (tuple_parse);
	}
	else if (tok_lst->type == LESSAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = new_node;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = new_node;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREATAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = new_node;
		return (tuple_parse);
	}
	else if (tok_lst->type == DGREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = create_ast_node(tok_lst, NULL, tok_lst->next);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = new_node;
		return (tuple_parse);
	}
	return (NULL);
}

/*
**	nb_tok - tok_lst->i >= 2:
**	This is use to check if we have enought token to use the function
*/

t_tuple	*isio_redirect(t_token *tok_lst, int nb_tok, int mv)
{
	int			tmp;
	t_tuple		*tuple_parse;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if ((tuple_parse = isio_file(tok_lst, nb_tok, 0)))
	{
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	else if (tok_lst->type == IO_NUMBER &&
			(tuple_parse = isio_file(tok_lst, nb_tok, 1)))
	{
		tuple_parse->ast_tree->left = create_ast_node(tok_lst, NULL, NULL);
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, tok_lst->next);
		return (tuple_parse);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = create_ast_node(tok_lst->next, tok_lst, tok_lst->next->next);
		return (tuple_parse);
	}
	return (NULL);
}


/*
**	The static [i] is here to avoid an infinity loop
**	4 * i - (i - 1) : this is to avoid an infinity loop too
**	-> It will begin with 3 and increase 2 by 2
*/

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

t_tuple	*iscmd_prefix(t_token *tok_lst, int nb_tok, int mv)
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
					&& tuple_parse->ast_tree->type == WORD)
			{
				max_tuple->ast_tree->left->content = ft_stradd(max_tuple->ast_tree->left->content, " ");
				max_tuple->ast_tree->left->content =
					ft_stradd(max_tuple->ast_tree->left->content, tuple_parse->ast_tree->content);
			}
			else
			{
				tuple_parse->ast_tree->left = max_tuple->ast_tree;
				max_tuple = tuple_parse;
			}
			max_tuple->mv = tuple_parse->mv;
		}
	}
	return (max_tuple);
}

void	change_last_left(t_ast_node	**ast_tree, t_token *tok_lst)
{
	char	*tmp_word;

	if ((*ast_tree)->left)
		change_last_left(&(*ast_tree)->left, tok_lst);
	else
	{
		if ((*ast_tree)->type == WORD)
		{
			tmp_word = ft_strdup((*ast_tree)->content);
			free((*ast_tree)->content);
			(*ast_tree)->content = ft_strjoin(tok_lst->content, " ");
			(*ast_tree)->content = ft_stradd((*ast_tree)->content, tmp_word);
		}
		else
			(*ast_tree)->left = create_ast_node(tok_lst, NULL, NULL);
	}
}

t_tuple	*is_simplecmd(t_token *tok_lst, int nb_tok, int mv)
{
	int		tmp;
	t_tuple	*tuple_parse;
	t_tuple	*tmp_tuple;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	tmp = mv;
	if ((tuple_parse = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
		if ((tmp_tuple = is_word(tok_lst, tuple_parse->mv)))
		{
			if (tuple_parse->ast_tree->type == WORD)
			{
				tuple_parse->ast_tree->content = ft_stradd(tuple_parse->ast_tree->content, " ");
				tuple_parse->ast_tree->content =
					ft_stradd(tuple_parse->ast_tree->content, tmp_tuple->ast_tree->content);
			}
			else
				tuple_parse->ast_tree->left = tmp_tuple->ast_tree;
			tuple_parse->mv = tmp_tuple->mv;
			if ((tmp_tuple = iscmd_prefix(tok_lst, nb_tok, tuple_parse->mv)))
			{
				if (!tuple_parse->ast_tree->left)
					tuple_parse->ast_tree->left = tmp_tuple->ast_tree;
				else
				{
					tmp_tuple->ast_tree->left = tuple_parse->ast_tree;
					tuple_parse->ast_tree = tmp_tuple->ast_tree;
				}
				tuple_parse->mv = tmp_tuple->mv;
				return (tuple_parse);
			}
		}
	}
	if ((tuple_parse = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
		if ((tmp_tuple = is_word(tok_lst, tuple_parse->mv)))
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = tmp_tuple->ast_tree;
			else
			{
				if (tuple_parse->ast_tree->type == WORD)
				{
					tuple_parse->ast_tree->content = ft_stradd(tuple_parse->ast_tree->content, " ");
					tuple_parse->ast_tree->content =
						ft_stradd(tuple_parse->ast_tree->content, tmp_tuple->ast_tree->content);
				}
				else
				{
					tmp_tuple->ast_tree->left = tuple_parse->ast_tree;
					tuple_parse = tmp_tuple;
				}
			}
			tuple_parse->mv = tmp_tuple->mv;
			return (tuple_parse);
		}
	}
	if (tok_lst->type == WORD && (tuple_parse = iscmd_prefix(tok_lst, nb_tok, 1)))
	{
		change_last_left(&tuple_parse->ast_tree, tok_lst);
		tuple_parse->mv += 1 + mv;
		return (tuple_parse);
	}
	if ((tmp_tuple = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
		tuple_parse = tmp_tuple;
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	if (tok_lst->type == WORD)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = 1;
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		return (tuple_parse);
	}
	return (NULL);
}

t_tuple	*ispipe(t_token *tok_lst, int mv)
{
	int		tmp;
	t_tuple	*new_tuple;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if (tok_lst->type == PIPE)
	{
		new_tuple = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		new_tuple->mv = mv + 1;
		new_tuple->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		return (new_tuple);
	}
	else
		return (NULL);
}

t_tuple	*isnewline(t_token *tok_lst, int mv)
{
	int		tmp;
	t_tuple	*new_tuple;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if (tok_lst->type == NEWLINE)
	{
		new_tuple = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		new_tuple->mv = mv + 1;
		new_tuple->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		return (new_tuple);
	}
	else
		return (NULL);
}

t_tuple	*ispipe_sequence(t_token *tok_lst, int nb_tok, int mv)
{
	int		tmp;
	t_tuple	*tmp_tuple;
	t_tuple	*max_tuple;
	t_tuple	*new_tuple;

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
	tmp = mv;
	if ((new_tuple = is_simplecmd(tok_lst, nb_tok, 0)))
	{
		max_tuple = new_tuple;
		while (42)
		{
			if ((tmp_tuple = ispipe(tok_lst, max_tuple->mv)))
			{
				tmp_tuple->ast_tree->left = max_tuple->ast_tree;
				if ((new_tuple = isnewline(tok_lst, tmp_tuple->mv)) &&
						(new_tuple = is_simplecmd(tok_lst, nb_tok, new_tuple->mv)))
				{
					tmp_tuple->ast_tree->right = new_tuple->ast_tree;
					max_tuple = tmp_tuple;
					max_tuple->mv = new_tuple->mv;
					continue ;
				}
				if ((new_tuple = is_simplecmd(tok_lst, nb_tok, tmp_tuple->mv)))
				{
					tmp_tuple->ast_tree->right = new_tuple->ast_tree;
					max_tuple = tmp_tuple;
					max_tuple->mv = new_tuple->mv;
					continue ;
				}
			}
			break;
		}
	}
	return (max_tuple);
}

t_tuple	*isand_or(t_token *tok_lst, int nb_tok, int mv)
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
	tmp = mv;
	if ((tuple_parse = ispipe_sequence(tok_lst, nb_tok, 0)))
	{
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	return (NULL);
}

t_tuple	*isseparator_op(t_token *tok_lst, int mv)
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
	if (tok_lst->type == SEMICOLON)
	{
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, NULL);
		tuple_parse->mv = mv + 1;
		return (tuple_parse);
	}
	else
		return (NULL);
}

t_tuple	*islist(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	t_tuple	*tuple_parse;
	t_tuple	*tmp_tuple;
	t_tuple	*max_tuple;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max_tuple = NULL;
	if ((tuple_parse = isand_or(tok_lst, nb_tok, 0)))
	{
		max_tuple = tuple_parse;
		while (42)
		{
			if ((tuple_parse = isseparator_op(tok_lst, max_tuple->mv)))
			{
				tuple_parse->ast_tree->left = max_tuple->ast_tree;
				if ((tmp_tuple = isand_or(tok_lst, nb_tok, tuple_parse->mv)))
				{
					tuple_parse->ast_tree->right = tmp_tuple->ast_tree;
					tuple_parse->mv = tmp_tuple->mv;
					max_tuple = tuple_parse;
					continue ;
				}
			}
			break ;
		}
	}
	return (max_tuple);
}

t_tuple	*iscomplete_cmd(t_token *tok_lst, int nb_tok, int mv)
{
	int		tmp;
	t_tuple	*tmp_tuple;
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
	if ((tuple_parse = islist(tok_lst, nb_tok, 0)))
	{
		if ((tmp_tuple = isseparator_op(tok_lst, tuple_parse->mv)))
		{
			tmp_tuple->ast_tree->left = tuple_parse->ast_tree;
			tmp_tuple->mv += mv;
			return (tmp_tuple);
		}
	}
	if ((tuple_parse = islist(tok_lst, nb_tok, 0)))
	{
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	return (NULL);
}

/*int	main(void)
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
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("cat");
	tok_lst->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->type = WORD;
	tok_lst->next->next->next->content = ft_strdup("-e");
	tok_lst->next->next->next->next = NULL;(t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->type = PIPE;
	tok_lst->next->next->next->next->content = ft_strdup("|");
	tok_lst->next->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->content = ft_strdup("wc");
	tok_lst->next->next->next->next->next->next = NULL;
	tuple_end = iscomplete_cmd(tok_lst, 4, 0);
	if (tuple_end)
	{
		printf("mv final = %d\n", tuple_end->mv);
		print_AST(tuple_end->ast_tree, 0, 0);
	}
}*/
