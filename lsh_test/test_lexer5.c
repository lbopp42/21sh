/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:18:17 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/03 10:22:59 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include "lsh_test.h"

t_token	*test_lexer5(int *nb_tok[], int curs)
{
	t_token				*tok_lst;
	t_token				*tmp;
	int					i;
	const t_tok_test	tok_array[] = {
		{WORD, "mkdir"},
		{WORD, "test"},
		{SEMICOLON, ";"},
		{WORD, "cd"},
		{WORD, "test"},
		{SEMICOLON, ";"},
		{WORD, "ls"},
		{WORD, "-a"},
		{SEMICOLON, ";"},
		{WORD, "ls"},
		{PIPE, "|"},
		{WORD, "cat"},
		{PIPE, "|"},
		{WORD, "wc"},
		{WORD, "-c"},
		{GREAT, ">"},
		{WORD, "fifi"},
		{SEMICOLON, ";"},
		{WORD, "cat"},
		{WORD, "fifi"},
		{0, NULL}	
	};
	t_state				*st_lst;
	int					error;

	error = 0;
	st_lst = NULL;
	tok_lst = NULL;
	g_line = NULL;
	g_line = ft_strdup("mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi");
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
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);
	return (tok_lst);
}
