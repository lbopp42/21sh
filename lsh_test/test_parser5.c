/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:20:08 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 09:38:39 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser5(t_token *tok_lst, int nb_tok)
{
	int	tmp;

	if (nb_tok == (tmp = iscomplete_cmd(tok_lst, nb_tok, 0)))
		printf("\033[32m[OK]   \033[0m[mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi]\n");
	else
	{
		printf("\033[31m[FAIL] \033[0m[mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi]\n");
		printf("nb_tok = %d et tmp = %d\n", nb_tok, tmp);
	}
}
