/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:32:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 13:38:38 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

/*void	print_AST(t_ast_node *ast_tree, int mode, int layer)
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
}*/

t_list		*create_new_list(char *content)
{
	t_list	*list;

	list = (t_list*)ft_memalloc(sizeof(t_list));
	list->content = ft_strdup(content);
	list->next = NULL;
	return (list);
}

t_ast_node	*create_ast_node(t_token *tok_root, t_token *tok_left, t_token *tok_right)
{
	t_ast_node	*new_node;

	new_node = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
	new_node->type = tok_root->type;
	new_node->content = create_new_list(tok_root->content);
	if (tok_left)
	{
		new_node->left = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->left->type = tok_left->type;
		new_node->left->content = create_new_list(tok_left->content);
		new_node->left->left = NULL;
		new_node->left->right = NULL;
	}
	else
		new_node->left = NULL;
	if (tok_right)
	{
		new_node->right = (t_ast_node*)ft_memalloc(sizeof(t_ast_node));
		new_node->right->type = tok_right->type;
		new_node->right->content = create_new_list(tok_right->content);
		new_node->right->right = NULL;
		new_node->right->left = NULL;
	}
	else
		new_node->right = NULL;
	return (new_node);
}

t_tuple	*create_tuple(t_token *root, t_token *left, t_token *right, int mv)
{
	t_tuple	*tuple_parse;

	tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
	tuple_parse->ast_tree = create_ast_node(root, left, right);
	tuple_parse->mv = mv;
	return (tuple_parse);
}

t_tuple	*isio_file(t_token *tok_lst, int mv)
{
	int			tmp;

	tmp = mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (NULL);
		tmp--;
	}
	if (tok_lst->type == LESS && tok_lst->next && tok_lst->next->type == WORD)
		return (create_tuple(tok_lst, NULL, tok_lst->next, mv + 2));
	else if (tok_lst->type == LESSAND && tok_lst->next && tok_lst->next->type == WORD)
		return (create_tuple(tok_lst, NULL, tok_lst->next, mv + 2));
	else if (tok_lst->type == GREAT && tok_lst->next && tok_lst->next->type == WORD)
		return (create_tuple(tok_lst, NULL, tok_lst->next, mv + 2));
	else if (tok_lst->type == GREATAND && tok_lst->next && tok_lst->next->type == WORD)
		return (create_tuple(tok_lst, NULL, tok_lst->next, mv + 2));
	else if (tok_lst->type == DGREAT && tok_lst->next && tok_lst->next->type == WORD)
		return (create_tuple(tok_lst, NULL, tok_lst->next, mv + 2));
	return (NULL);
}

/*
**	The if (!first) is here if last is a WORD.
**	example : ls >&-
**********************************************
**	The if (new_tuple->ast_tree->left) is here
**	if we have IO_NUMBER or not.
**	example: ls 1>&-
*/

t_tuple	*push_redir(t_tuple *new_tuple, t_tuple *last)
{
	t_ast_node	*tmp;
	t_ast_node	*tmp_word;
	t_ast_node	*first;

	tmp = last->ast_tree;
	first = NULL;
	while (tmp->left)
	{
		first = tmp;
		tmp = tmp->left;
	}
	if (tmp->type == WORD)
	{
		tmp_word = tmp;
		if (!first)
			last->ast_tree = new_tuple->ast_tree;
		else
			first->left = new_tuple->ast_tree;
		if (new_tuple->ast_tree->left)
		{
			new_tuple->ast_tree->left->left = tmp_word;
			new_tuple->ast_tree->left->left->left = NULL;
			new_tuple->ast_tree->left->left->right = NULL;
		}
		else
		{
			new_tuple->ast_tree->left = tmp_word;
			new_tuple->ast_tree->left->left = NULL;
			new_tuple->ast_tree->left->right = NULL;
		}
	}
	else
		tmp->left = new_tuple->ast_tree;
	last->mv += new_tuple->mv;
	return (last);
}

void	add_to_list(t_list **list, char *content)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_new_list(content);
}

t_list	*here_doc(char *delimiter, int option)
{
	static t_heredoc	*hd_list = NULL;
	t_heredoc			*tmp_list;
	char				*line;
	t_list				*list;

	if (option == 1)
	{
		line = NULL;
		if (!hd_list)
		{
			hd_list = (t_heredoc*)ft_memalloc(sizeof(t_heredoc));
			hd_list->content = NULL;
			while (1)
			{
				ft_putstr("heredoc> ");
				get_next_line(0, &line);
				if (ft_strequ(line, delimiter))
					break ;
				if (!hd_list->content)
				{
					line = ft_stradd(line, "\n");
					hd_list->content = create_new_list(line);
				}
				else
				{
					line = ft_stradd(line, "\n");
					add_to_list(&hd_list->content, line);
				}
				ft_strdel(&line);
			}
			hd_list->next = NULL;
		}
		else
		{
			tmp_list = hd_list;
			while (tmp_list->next)
				tmp_list = tmp_list->next;
			tmp_list->next = (t_heredoc*)ft_memalloc(sizeof(t_heredoc));
			tmp_list->next->content = NULL;
			while (1)
			{
				ft_putstr("heredoc> ");
				get_next_line(0, &line);
				if (ft_strequ(line, delimiter))
					break ;
				if (!tmp_list->next->content)
				{
					line = ft_stradd(line, "\n");
					tmp_list->next->content = create_new_list(line);
				}
				else
				{
					line = ft_stradd(line, "\n");
					add_to_list(&tmp_list->next->content, line);
				}
				ft_strdel(&line);
			}
			tmp_list->next->next = NULL;
		}
	}
	else if (!option)
	{
		list = hd_list->content;
		hd_list = hd_list->next;
		return (list);
	}
	return (NULL);
}

t_tuple	*isio_redirect(t_token *tok_lst, t_tuple *last)
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
	if ((tuple_parse = isio_file(tok_lst, 0)))
	{
		if ((tuple_parse->ast_tree->type == GREATAND ||
				tuple_parse->ast_tree->type == LESSAND) && last)
			tuple_parse = push_redir(tuple_parse, last);
		else if (last)
		{
			tuple_parse->ast_tree->left = last->ast_tree;
			tuple_parse->mv += mv;
		}
		else
			tuple_parse->mv += mv;
		return (tuple_parse);
	}
	else if (tok_lst->type == IO_NUMBER &&
			(tuple_parse = isio_file(tok_lst, 1)))
	{
		tuple_parse->ast_tree->left = create_ast_node(tok_lst, NULL, NULL);
		if ((tuple_parse->ast_tree->type == GREATAND ||
				tuple_parse->ast_tree->type == LESSAND) && last)
			tuple_parse = push_redir(tuple_parse, last);
		else if (last)
		{
			tuple_parse->ast_tree->left->left = last->ast_tree;
			tuple_parse->mv += mv;
		}
		else
			tuple_parse->mv += mv;
		return (tuple_parse);
	}
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
	{
		here_doc(tok_lst->next->content, 1);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 2;
		tuple_parse->ast_tree = create_ast_node(tok_lst, NULL, tok_lst->next);
		if (last)
			tuple_parse->ast_tree->left = last->ast_tree;
		return (tuple_parse);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
	{
		here_doc(tok_lst->next->next->content, 1);
		tuple_parse = (t_tuple*)ft_memalloc(sizeof(t_tuple));
		tuple_parse->mv = mv + 3;
		tuple_parse->ast_tree = create_ast_node(tok_lst->next, tok_lst, tok_lst->next->next);
		if (last)
			tuple_parse->ast_tree->left->left = last->ast_tree;
		return (tuple_parse);
	}
	return (NULL);
}

void	add_to_last_left(t_ast_node **ast_tree, t_token *tok_lst)
{
	if ((*ast_tree)->left)
		add_to_last_left(&(*ast_tree)->left, tok_lst);
	else
	{
		if ((*ast_tree)->type == WORD)
			add_to_list(&(*ast_tree)->content, tok_lst->content);
		else
			(*ast_tree)->left = create_ast_node(tok_lst, NULL, NULL);
	}
}

t_tuple	*is_word(t_token *tok_lst, t_tuple *last)
{
	int			tmp;

	tmp = (last) ? last->mv : 0;
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
		if (!last)
		{
			last = (t_tuple*)ft_memalloc(sizeof(t_tuple));
			last->ast_tree = create_ast_node(tok_lst, NULL, NULL);
			last->mv = 1;
		}
		else
		{
			add_to_last_left(&last->ast_tree, tok_lst);
			last->mv += 1;
		}
		return (last);
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
	(void)nb_tok;
	if ((tuple_parse = isio_redirect(tok_lst, NULL)) || (tuple_parse = is_word(tok_lst, 0)))
	{
		max_tuple = tuple_parse;
		while ((tuple_parse = isio_redirect(tok_lst, max_tuple)) ||
				(tuple_parse = is_word(tok_lst, max_tuple)))
			max_tuple = tuple_parse;
	}
	return (max_tuple);
}

t_token	*move_to_real_token(t_token *tok_lst, int mv)
{
	while (mv > 0)
	{
		tok_lst = tok_lst->next;
		mv -= 1;
	}
	return (tok_lst);
}

t_tuple	*is_simplecmd(t_token *tok_lst, int nb_tok, int mv)
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
	/*if ((tuple_parse = iscmd_prefix(tok_lst, nb_tok, 0)))
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
				add_to_the_last_left(&tuple_parse, move_to_real_token(tok_lst, tuple->mv));
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
				print_AST(tuple_parse->ast_tree, 0, 0);
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
		if (!last_tuple)
			change_last_left(&tuple_parse->ast_tree, tok_lst);
		else
		{
			if (tuple_parse->ast_tree->type == WORD)
			{
				tmp_string = ft_strdup(tuple_parse->ast_tree->content);
				free(tuple_parse->ast_tree->content);
				tuple_parse->ast_tree->content = ft_strdup(tok_lst->content);
				tuple_parse->ast_tree->content = ft_stradd(tuple_parse->ast_tree->content, " ");
				tuple_parse->ast_tree->content = ft_stradd(tuple_parse->ast_tree->content, tmp_string);
				last_tuple->ast_tree->right = tuple_parse->ast_tree;
				tuple_parse->ast_tree = last_tuple->ast_tree;
			}
			else
			{
				last_tuple->ast_tree->right = create_ast_node(tok_lst, NULL, NULL);
				if (tuple_parse->ast_tree->left && tuple_parse->ast_tree->left->type == WORD)
				{
					last_tuple->ast_tree->right->content =
						ft_stradd(last_tuple->ast_tree->right->content, " ");	
					last_tuple->ast_tree->right->content =
						ft_stradd(last_tuple->ast_tree->right->content, tuple_parse->ast_tree->left->content);	
				tuple_parse->ast_tree->left = last_tuple->ast_tree;
				}
			}
		}
		tuple_parse->mv += 1 + mv;
		return (tuple_parse);
	}*/
	if ((tuple_parse = iscmd_prefix(tok_lst, nb_tok, 0)))
	{
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

int		isnewline(t_token *tok_lst, t_tuple **last_tuple)
{
	int	tmp;

	tmp = (*last_tuple)->mv;
	while (tmp > 0)
	{
		if (tok_lst->next)
			tok_lst = tok_lst->next;
		else
			return (0);
		tmp--;
	}
	if (tok_lst->type == NEWLINE)
	{
		(*last_tuple)->mv += 1;
		return (1);
	}
	else
		return (0);
}

void	go_to_left(t_ast_node **ast_old, t_ast_node *ast_pipe)
{
	static t_ast_node *first = NULL;

	if ((*ast_old)->left && (*ast_old)->type != GREATAND && (*ast_old)->type != LESSAND)
	{
		first = *ast_old;
		go_to_left(&(*ast_old)->left, ast_pipe);
	}
	else
	{
		ast_pipe->right = *ast_old;
		first->left = ast_pipe;
	}
}

/*
**	if (new_tuple->ast_tree->type != WORD) is here to order pipe and redir
**	example: ls | cat | wc -c > fifi
*/

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
				if (isnewline(tok_lst, &tmp_tuple) &&
						(new_tuple = is_simplecmd(tok_lst, nb_tok, tmp_tuple->mv)))
				{
					tmp_tuple->ast_tree->right = new_tuple->ast_tree;
					tmp_tuple->mv = new_tuple->mv;
					max_tuple = tmp_tuple;
					continue ;
				}
				if ((new_tuple = is_simplecmd(tok_lst, nb_tok, tmp_tuple->mv)))
				{
					if (new_tuple->ast_tree->type != WORD && new_tuple->ast_tree->type != GREATAND
							&& new_tuple->ast_tree->type != LESSAND)
					{
						go_to_left(&new_tuple->ast_tree, tmp_tuple->ast_tree);
						tmp_tuple->ast_tree = new_tuple->ast_tree;
					}
					else
						tmp_tuple->ast_tree->right = new_tuple->ast_tree;
					tmp_tuple->mv = new_tuple->mv;
					max_tuple = tmp_tuple;
					/*printf("========= MAX_TUPLE ==============\n");
					print_AST(max_tuple->ast_tree, 0, 0);*/
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
	//t_tuple	*tmp_tuple;
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
	/*if ((tuple_parse = islist(tok_lst, nb_tok, 0)))
	{
		if ((tmp_tuple = isseparator_op(tok_lst, tuple_parse->mv)))
		{
			tmp_tuple->ast_tree->left = tuple_parse->ast_tree;
			tmp_tuple->mv += mv;
			return (tmp_tuple);
		}
	}*/
	if ((tuple_parse = islist(tok_lst, nb_tok, 0)))
	{
		tuple_parse->mv += mv;
		return (tuple_parse);
	}
	return (NULL);
}

//TODO GREATAND AND LESSAND WITH PIPE

/*int	main(void)
{
	t_tuple	*tuple_end;
	t_token	*tok_lst;

	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->type = PIPE;
	tok_lst->next->content = ft_strdup("|");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("cat");
	tok_lst->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->type = GREAT;
	tok_lst->next->next->next->content = ft_strdup(">");
	tok_lst->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->content = ft_strdup("file");
	tok_lst->next->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->type = GREATAND;
	tok_lst->next->next->next->next->next->content = ft_strdup(">&");
	tok_lst->next->next->next->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->next->content = ft_strdup("-");
	tok_lst->next->next->next->next->next->next->next = NULL;(t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->next->next->content = ft_strdup("fifi");
	tok_lst->next->next->next->next->next->next->next->next = NULL;(t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->next->next->next->next->next->type = WORD;
	tok_lst->next->next->next->next->next->next->next->next->content = ft_strdup("-");
	tok_lst->next->next->next->next->next->next->next->next->next = NULL;
	tuple_end = iscomplete_cmd(tok_lst, 4, 0);
	printf("ON SORT DE LA!\n");
	if (tuple_end)
	{
		printf("mv final = %d\n", tuple_end->mv);
		printf("ICI\n");
		print_AST(tuple_end->ast_tree, 0, 0);
	}
}*/
