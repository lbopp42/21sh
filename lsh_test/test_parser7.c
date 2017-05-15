/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:41:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/15 15:12:48 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser7(t_token *tok_lst, int nb_tok)
{
	t_tuple	*tmp;

	tmp = iscomplete_cmd(tok_lst, nb_tok, 0);
	if (nb_tok == tmp->mv)
		printf("\033[32m[OK]   \033[0m[ls | cat | wc | NEWLINE echo]\n");
	else
	{
		printf("\033[31m[FAIL] \033[0m[ls | cat | wc | NEWLINE echo]\n");
	}
}
