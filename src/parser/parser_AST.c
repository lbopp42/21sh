/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:32:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/11 13:41:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

t_tuple	*isio_file(t_token *tok_lst, int nb_tok, t_tuple *tuple_parse)
{
	int			tmp;
	t_ast_node	*new_node;

	tmp = 0;
	if (tuple_parse)
		tmp = tuple_parse->mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	(void)nb_tok;
	if (tok_lst->type == LESS && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->type = LESS;
		new_node->content = ft_strdup("<");
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = WORD;
		new_node->right->content = ft_strdup(tok_lst->next->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
		new_node->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = new_node;
			else
				tuple_parse->ast_tree->right = new_node;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = new_node;
		}
		tuple_parse->mv += 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == LESSAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->type = LESSAND;
		new_node->content = ft_strdup("<&");
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = WORD;
		new_node->right->content = ft_strdup(tok_lst->next->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
		new_node->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = new_node;
			else
				tuple_parse->ast_tree->right = new_node;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = new_node;
		}
		tuple_parse->mv += 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->type = GREAT;
		new_node->content = ft_strdup(">");
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = WORD;
		new_node->right->content = ft_strdup(tok_lst->next->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
		new_node->left = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->left->type = WORD;
		new_node->left->content = ft_strdup("test");
		new_node->left->right = NULL;
		new_node->left->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = new_node;
			else
				tuple_parse->ast_tree->right = new_node;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = new_node;
		}
		tuple_parse->mv += 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == GREATAND && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->type = GREATAND;
		new_node->content = ft_strdup(">&");
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = WORD;
		new_node->right->content = ft_strdup(tok_lst->next->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
		new_node->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = new_node;
			else
				tuple_parse->ast_tree->right = new_node;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = new_node;
		}
		tuple_parse->mv += 2;
		return (tuple_parse);
	}
	else if (tok_lst->type == DGREAT && tok_lst->next && tok_lst->next->type == WORD)
	{
		new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->type = DGREAT;
		new_node->content = ft_strdup(">>");
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = WORD;
		new_node->right->content = ft_strdup(tok_lst->next->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
		new_node->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = new_node;
			else
				tuple_parse->ast_tree->right = new_node;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = new_node;
		}
		tuple_parse->mv += 2;
		return (tuple_parse);
	}
	return (NULL);
}

void	print_AST(t_ast_node *ast_tree)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		print_AST(ast_tree->left);
	printf("tree = [%s]\n", ast_tree->content);
	if (ast_tree->right)
		print_AST(ast_tree->right);
}

/*
**	nb_tok - tok_lst->i >= 2:
**	This is use to check if we have enought token to use the function
*/

t_tuple	*isio_redirect(t_token *tok_lst, int nb_tok, t_tuple *tuple_parse)
{
	t_tuple	*tmp;

	tmp = tuple_parse;
	while (tmp && tmp->mv > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp->mv -= 1;
	}
	if ((tmp = isio_file(tok_lst, nb_tok, 0)))
	{
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = tmp->ast_tree;
			else
				tuple_parse->ast_tree->right = tmp->ast_tree;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = tmp->ast_tree;
		}
		tuple_parse->mv = tmp->mv + tuple_parse->mv;
		return (tuple_parse);
	}
	if (tmp)
	{
		tmp->mv = 1;
		tmp->ast_tree = tuple_parse->ast_tree;
	}
	else
	{
		tmp = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tmp->mv = 1;
		tmp->ast_tree = NULL;
	}
	if (tok_lst->type == IO_NUMBER &&
			(tmp = isio_file(tok_lst, nb_tok, tmp)))
	{
		tmp->ast_tree->left = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		tmp->ast_tree->left->type = IO_NUMBER;
		tmp->ast_tree->left->content = ft_strdup(tok_lst->content);
		tmp->ast_tree->left->right = NULL;
		tmp->ast_tree->left->left = NULL;
		if (tuple_parse && tuple_parse->ast_tree)
		{
			if (!tuple_parse->ast_tree->left)
				tuple_parse->ast_tree->left = tmp->ast_tree;
			else
				tuple_parse->ast_tree->right = tmp->ast_tree;
		}
		else
		{
			if (!tuple_parse)
				tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			tuple_parse->ast_tree = tmp->ast_tree;
		}
		tuple_parse->mv = tmp->mv + tuple_parse->mv;
		return (tuple_parse);
	}
	/*else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
			return (2 + mv);
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
			return (3 + mv);*/
	return (NULL);
}

/*
**	The static [i] is here to avoid an infinity loop
**	4 * i - (i - 1) : this is to avoid an infinity loop too
**	-> It will begin with 3 and increase 2 by 2
*/

int	is_word(t_token *tok_lst, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == WORD)
		return (mv + 1);
	else
		return (0);
}

int	iscmd_prefix(t_token *tok_lst, int nb_tok, t_tuple *tuple_parse)
{
	t_tuple	*tmp;
	t_tuple	*new_node;
	int	max;

	tmp = tuple_parse;
	while (tmp && tmp->mv > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	tmp = tuple_parse;
	if ((new_node = isio_redirect(tok_lst, nb_tok, tmp)) || (new_node->mv = is_word(tok_lst, tmp->mv)))
	{
		max = mv;
		while ((mv = isio_redirect(tok_lst, nb_tok, max)) || (new_node->mv = is_word(tok_lst, max)))
			max = mv;
	}
	return (max);
}

int	main(void)
{
	t_tuple	*tuple_parse;
	t_token	*tok_lst;

	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->type = IO_NUMBER;
	tok_lst->content = ft_strdup("1");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->type = DGREAT;
	tok_lst->next->content = ft_strdup(">>");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("file");
	tok_lst->next->next->next = NULL;
	printf("JUSQUE LA C'EST BON\n");
	tuple_parse = NULL;
	tuple_parse = isio_redirect(tok_lst, 3, tuple_parse);
	print_AST(tuple_parse->ast_tree);
	printf("mv = %d\n", tuple_parse->mv);
	return (0);
}

/*int	is_simplecmd(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	tmp = mv;
	if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)) && (mv = is_word(tok_lst, mv)) &&
			(mv = iscmd_prefix(tok_lst, nb_tok, mv)))
	{
		return (tmp + mv);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)) && (mv = is_word(tok_lst, mv)))
	{
		return (tmp + mv);
	}
	else if (tok_lst->type == WORD && (mv = iscmd_prefix(tok_lst, nb_tok, 1)))
	{
		return (tmp + mv + 1);
	}
	else if ((mv = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
		return (tmp + mv);
	}
	else if (tok_lst->type == WORD)
	{
		return (tmp + 1);
	}
	return (0);
}

int	ispipe(t_token *tok_lst, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == PIPE)
		return (mv + 1);
	else
		return (0);
}

int	isnewline(t_token *tok_lst, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == NEWLINE)
		return (mv + 1);
	else
		return (0);
}

int	ispipe_sequence(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	int	max;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	tmp = mv;
	if ((mv = is_simplecmd(tok_lst, nb_tok, 0)))
	{
		max = mv;
		while ((mv = ispipe(tok_lst, max)) && (tmp = mv) &&
				(((mv = isnewline(tok_lst, tmp)) && (mv = is_simplecmd(tok_lst, nb_tok, mv))) || (mv = is_simplecmd(tok_lst, nb_tok, tmp))))
			max = mv;
	}
	return (max);
}

int	isand_or(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	tmp = mv;
	if ((mv = ispipe_sequence(tok_lst, nb_tok, 0)))
		return (tmp + mv);
	return (0);
}

int	isseparator_op(t_token *tok_lst, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == SEMICOLON)
		return (mv + 1);
	else
		return (0);
}

int	islist(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;
	int	max;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	max = 0;
	if ((mv = isand_or(tok_lst, nb_tok, mv)))
	{
		max = mv;
		while ((mv = isseparator_op(tok_lst, mv)) && (mv = isand_or(tok_lst, nb_tok, mv)))
			max = mv;
	}
	return (max);
}

int	iscomplete_cmd(t_token *tok_lst, int nb_tok, int mv)
{
	int	tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if ((mv = islist(tok_lst, nb_tok, 0)) && (mv = isseparator_op(tok_lst, mv)))
		return (mv);
	else if ((mv = islist(tok_lst, nb_tok, 0)))
		return (mv);
	else
		return (0);
}*/
