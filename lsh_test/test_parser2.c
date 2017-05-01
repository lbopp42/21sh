/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 12:37:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/01 12:51:37 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser2(t_token *tok_lst, int nb_tok)
{
	/*(void)nb_tok;
	while (tok_lst)
	{
		printf("content = [%s] et type = [%d]\n", tok_lst->content, tok_lst->type);
		tok_lst = tok_lst->next;
	}*/
	int	tmp;

	if (nb_tok == (tmp = iscomplete_cmd(tok_lst, nb_tok, 0)))
		printf("\033[32m[OK]   \033[0m[ls | cat ; test >> lol]\n");
	else
	{
		printf("\033[31m[FAIL] \033[0m[ls | cat ; test >> lol]\n");
		printf("nb_tok = %d et tmp = %d\n", nb_tok, tmp);
	}
}
