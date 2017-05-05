/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:39:18 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 10:05:37 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"
#include "lsh.h"

t_token	*test_lexer7(int *nb_tok[], int curs)
{
	t_token				*tok_lst;
	t_token				*tmp;
	int					i;
	const t_tok_test	tok_array[] = {
		{WORD, "ls"},
		{PIPE, "|"},
		{WORD, "cat"},
		{PIPE, "|"},
		{WORD, "wc"},
		{PIPE, "|"},
		{NEWLINE, "\n"},
		{WORD, "echo"},
		{0, NULL}
	};
	t_state				*st_lst;
	int					error;

	error = 0;
	st_lst = NULL;
	tok_lst = NULL;
	g_line = NULL;
	g_line = ft_strdup("ls | cat | wc | \n echo");
	(*nb_tok)[curs] = lexer_posix(&tok_lst, &st_lst);
	free(g_line);
	i = 0;
	tmp = tok_lst;
	while (tok_array[i].content && tmp)
	{
		if (tok_array[i].type != tmp->type)
			error++;
		if (ft_strcmp(tok_array[i].content, tmp->content))
			error++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array[i].content || tmp || error || st_lst)
		printf("\033[32m[OK]   \033[0m");
	else
		printf("\033[31m[FAIL] \033[0m");
	printf("[ls | cat | wc | NEWLINE echo]\n");
	return (tok_lst);
}
