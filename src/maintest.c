/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:38:12 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/01 09:41:23 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

void	lexer_posix(t_token **tok_lst, t_state **st_lst);

typedef struct	s_tok_test
{
	int		type;
	char	*content;
}				t_tok_test;

/*
** Main to test lsh
*/

int	main(void)
{
	t_token		*tok_lst;
	t_token		*tmp;
	int			i;
	int			errortype;
	int			errortoken;
	t_state		*state_lst;
	const t_tok_test	tok_array1[] = {{WORD, "ls"}, {0, NULL}};
	const t_tok_test	tok_array2[] = {
		{WORD, "ls"},
		{PIPE, "|"},
		{WORD, "cat"},
		{SEMICOLON, ";"},
		{WORD, "test"},
		{DGREAT, ">>"},
		{WORD, "lol"},
		{0, NULL}
	};
	const t_tok_test	tok_array3[] = {
		{WORD, "ls"},
		{PIPE, "|"},
		{WORD, "cat"},
		{SEMICOLON, ";"},
		{WORD, "test"},
		{DGREAT, ">>"},
		{WORD, "lol"},
		{0, NULL}	
	};
	const	t_tok_test	tok_array4[] = {
		{WORD, "echo"},
		{WORD, "\"test\"\"test2\""},
		{0, NULL}	
	};
	const t_tok_test	tok_array5[] = {
		{WORD, "echo"},
		{WORD, "\"ls ; `cat`\"\"test2\""},
		{0, NULL}	
	};
	const t_tok_test	tok_array6[] = {
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
	const t_tok_test	tok_array7[] = {
		{WORD, "ls"},
		{SEMICOLON, ";"},
		{WORD, "cat"},
		{0, NULL}
	};
	const t_tok_test	tok_array8[] = {
		{0, NULL}
	};
	const t_tok_test	tok_array9[] = {
		{0, NULL}
	};
	const t_tok_test	tok_array10[] = {
		{WORD, "\"ls\""},
		{0, NULL}
	};
	const t_tok_test	tok_array11[] = {
		{WORD, "ls"},
		{0, NULL}
	};
	const t_tok_test	tok_array12[] = {
		{WORD, "ls"},
		{PIPE, "|"},
		{GREAT, ">"},
		{WORD, "file"},
		{0, NULL}
	};

	state_lst = NULL;
	printf("\n\033[36m=========  Testing lexer of lsh  =========\n\n\033[0m");
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	g_line = NULL;
	g_line = ft_strdup("ls");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array1[i].content && tmp)
	{
		if (tok_array1[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array1[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array1[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*			TEST 2		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls | cat ; test >> lol");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array2[i].content && tmp)
	{
		if (tok_array2[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array2[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array2[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 3		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls| cat ;test>>lol");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array3[i].content && tmp)
	{
		if (tok_array3[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array3[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array3[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 4		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("echo \"test\"\"test2\"");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array4[i].content && tmp)
	{
		if (tok_array4[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array4[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array4[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 5		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("echo \"ls ; `cat`\"\"test2\"");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array5[i].content && tmp)
	{
		if (tok_array5[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array5[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array5[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 6		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array6[i].content && tmp)
	{
		if (tok_array6[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array6[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array6[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 7		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls       ;         cat");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array7[i].content && tmp)
	{
		if (tok_array7[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array7[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array7[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 8		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("\"'\"'");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array8[i].content && tmp)
	{
		if (tok_array8[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array8[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken || !state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 9		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array9[i].content && tmp)
	{
		if (tok_array9[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array9[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array9[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 10		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("\"ls\"");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array10[i].content && tmp)
	{
		if (tok_array10[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array10[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array10[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m%d, %d", errortype, errortoken);
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 11		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("       ls");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array11[i].content && tmp)
	{
		if (tok_array11[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array11[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array11[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 12		*/
	state_lst = NULL;
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls | > file");
	lexer_posix(&tok_lst, &state_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array12[i].content && tmp)
	{
		if (tok_array12[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array12[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (tok_array12[i].content || tmp || errortype || errortoken || state_lst)
		printf("\033[31m[FAIL] \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		End of Test		*/
	printf("\n\033[36m===========================================\n\033[0m");
	return (0);
}
