/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:49:21 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/24 14:22:35 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	is_simplecmd(t_token *tok_lst, int nb_tok, int *max);

int	test1(void)
{
	int	max;
	int	nb_tok;
	t_token	*tok_lst;

	max = 0;
	nb_tok = 1;
	tok_lst= (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = NULL;
	if (is_simplecmd(tok_lst, nb_tok, &max) && max == nb_tok - 1)
		return (1);
	else
		return (0);
}

int	test2(void)
{
	int	max;
	int	nb_tok;
	t_token	*tok_lst;

	max = 0;
	nb_tok = 2;
	tok_lst= (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = GREAT;
	tok_lst->next->content = ft_strdup(">");
	tok_lst->next->next = NULL;
	if (is_simplecmd(tok_lst, nb_tok, &max) && max == nb_tok - 1)
		return (1);
	else
		return (0);
}

int	test3(void)
{
	int	max;
	int	nb_tok;
	t_token	*tok_lst;

	max = 0;
	nb_tok = 2;
	tok_lst= (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = GREAT;
	tok_lst->content = ft_strdup(">");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = WORD;
	tok_lst->next->content = ft_strdup("ls");
	tok_lst->next->next = NULL;
	if (is_simplecmd(tok_lst, nb_tok, &max) && max == nb_tok - 1)
		return (1);
	else
		return (0);
}

int	test4(void)
{	
	int	max;
	int	nb_tok;
	t_token	*tok_lst;
	int	test;

	max = 0;
	nb_tok = 3;
	tok_lst= (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = GREAT;
	tok_lst->content = ft_strdup(">");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = WORD;
	tok_lst->next->content = ft_strdup("ls");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->i = 2;
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("cat");
	tok_lst->next->next->next = NULL;
	if ((test = is_simplecmd(tok_lst, nb_tok, &max)) && max == nb_tok - 1)
		return (1);
	else
	{
		printf("TEST = %d et max = %d\n", test, max);
		return (0);
	}
}

void	launch_test_1to25(void)
{
	if (test1())
		printf("\033[32m[OK] \033[0m[ls]\n");
	else
		printf("\033[31m[FAIL] \033[0m[ls]\n");
	if (!test2())
		printf("\033[32m[OK] \033[0m[ls >]\n");
	else
		printf("\033[31m[FAIL] \033[0m[ls >]\n");
	if (test3())
		printf("\033[32m[OK] \033[0m[> ls]\n");
	else
		printf("\033[31m[FAIL] \033[0m[> ls]\n");
	if (test4())
		printf("\033[32m[OK] \033[0m[> ls cat]\n");
	else
		printf("\033[31m[FAIL] \033[0m[> ls cat]\n");
}

int	main(void)
{
	printf("\033[36m=========  Testing parser of lsh  =========\n\n\033[0m");
	launch_test_1to25();
}
