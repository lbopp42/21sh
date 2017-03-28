/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 12:38:12 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/27 16:05:22 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

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
	t_tok_test	tok_array1[] = {{WORD, "ls"}, {0, NULL}};
	t_tok_test	tok_array2[] = {
		{WORD, "ls"},
		{BLANK, " "},
		{PIPE, "|"},
		{BLANK, " "},
		{WORD, "cat"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "test"},
		{BLANK, " "},
		{DGREAT, ">>"},
		{BLANK, " "},
		{WORD, "lol"},
		{0, NULL}
	};
	t_tok_test	tok_array3[] = {
		{WORD, "ls"},
		{PIPE, "|"},
		{BLANK, " "},
		{WORD, "cat"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{WORD, "test"},
		{DGREAT, ">>"},
		{WORD, "lol"},
		{0, NULL}	
	};
	t_tok_test	tok_array4[] = {
		{WORD, "echo"},
		{BLANK, " "},
		{DQUOTE, "\""},
		{DQUOTE, "test"},
		{DQUOTE, "\""},
		{DQUOTE, "\""},
		{DQUOTE, "test2"},
		{DQUOTE, "\""},
		{0, NULL}	
	};
	t_tok_test	tok_array5[] = {
		{WORD, "echo"},
		{BLANK, " "},
		{DQUOTE, "\""},
		{DQUOTE, "ls ; "},
		{BQUOTE, "`"},
		{BQUOTE, "cat"},
		{DQUOTE, "`"},
		{DQUOTE, "\""},
		{DQUOTE, "\""},
		{DQUOTE, "test2"},
		{DQUOTE, "\""},
		{0, NULL}	
	};
	t_tok_test	tok_array6[] = {
		{WORD, "mkdir"},
		{BLANK, " "},
		{WORD, "test"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "cd"},
		{BLANK, " "},
		{WORD, "test"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "ls"},
		{BLANK, " "},
		{WORD, "-a"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "ls"},
		{BLANK, " "},
		{PIPE, "|"},
		{BLANK, " "},
		{WORD, "cat"},
		{BLANK, " "},
		{PIPE, "|"},
		{BLANK, " "},
		{WORD, "wc"},
		{BLANK, " "},
		{WORD, "-c"},
		{BLANK, " "},
		{GREAT, ">"},
		{BLANK, " "},
		{WORD, "fifi"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "cat"},
		{BLANK, " "},
		{WORD, "fifi"},
		{0, NULL}	
	};
	t_tok_test	tok_array7[] = {
		{WORD, "ls"},
		{BLANK, " "},
		{SEMICOLON, ";"},
		{BLANK, " "},
		{WORD, "cat"},
		{0, NULL}
	};

	printf("\n\033[36m=========  Testing lexer of lsh  =========\n\n\033[0m");
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	g_line = NULL;
	g_line = ft_strdup("ls");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array1[i].content)
	{
		if (tok_array1[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array1[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*			TEST 2		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls | cat ; test >> lol");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array2[i].content)
	{
		if (tok_array2[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array2[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 3		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls| cat ;test>>lol");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array3[i].content)
	{
		if (tok_array3[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array3[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 4		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("echo \"test\"\"test2\"");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array4[i].content)
	{
		if (tok_array4[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array4[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 5		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("echo \"ls ; `cat`\"\"test2\"");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array5[i].content)
	{
		if (tok_array5[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array5[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 6		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array6[i].content)
	{
		if (tok_array6[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array6[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		TEST 7		*/
	errortype = 0;
	errortoken = 0;
	tok_lst = NULL;
	free(g_line);
	g_line = NULL;
	g_line = ft_strdup("ls       ;         cat");
	get_token(&tok_lst);
	i = 0;
	tmp = tok_lst;
	while (tok_array7[i].content)
	{
		if (tok_array7[i].type != tmp->type)
			errortype++;
		if (ft_strcmp(tok_array7[i].content, tmp->content))
			errortoken++;
		i++;
		tmp = tmp->next;
	}
	if (errortype || errortoken)
		printf("\033[31m[FAIL]   \033[0m");
	else
		printf("\033[32m[OK]   \033[0m");
	printf("[%s]\n", g_line);

	/*		End of Test		*/
	printf("\n\033[36m===========================================\n\033[0m");
	return (0);
}
