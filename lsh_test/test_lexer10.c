/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:28:15 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 10:33:36 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include "lsh_test.h"

t_token	*test_lexer10(int *nb_tok[], int curs)
{
	t_token				*tok_lst;
	t_token				*tmp;
	int					i;
	const	t_tok_test	tok_array[] = {
		{0, NULL}	
	};
	t_state				*st_lst;
	int					error;

	error = 0;
	st_lst = NULL;
	tok_lst = NULL;
	g_line = NULL;
	g_line = ft_strdup("           ");
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
