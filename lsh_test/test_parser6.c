/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:36:26 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/17 15:34:25 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

static char	**ast_to_array(char *content)
{
	static int	i = 0;
	static char	*array[3];

	if (!content)
		return (array);
	array[i] = ft_strdup(content);
	i += 1;
	return (NULL);
}

static void	check_ast_tree(t_ast_node *ast_tree)
{
	if (!ast_tree)
		return ;
	if (ast_tree->left)
		check_ast_tree(ast_tree->left);
	if (ast_tree->right)
		check_ast_tree(ast_tree->right);
	ast_to_array(ast_tree->content);
}

static int	is_valid_ast(t_ast_node *ast_tree)
{
	char		**array;
	const char	*array_ref[4] = {"ls", "cat", "|", NULL};
	int			i;

	check_ast_tree(ast_tree);
	array = ast_to_array(NULL);
	i = 0;
	while (array_ref[i])
	{
		if (!ft_strequ(array[i], array_ref[i]))
			return (0);
		i += 1;
	}
	return (1);
}

void	test_parser6(t_token *tok_lst, int nb_tok)
{
	t_tuple	*tmp;

	tmp = iscomplete_cmd(tok_lst, nb_tok, 0);
	if (nb_tok == tmp->mv && is_valid_ast(tmp->ast_tree))
		printf("\033[32m[OK]   \033[0m[ls | cat]\n");
	else
	{
		printf("\033[31m[FAIL] \033[0m[ls | cat]\n");
	}
}
