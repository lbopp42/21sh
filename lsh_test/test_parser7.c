/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:41:50 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 09:50:44 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser7(t_token *tok_lst, int nb_tok)
{
	if (nb_tok == iscomplete_cmd(tok_lst, nb_tok, 0))
		printf("\033[32m[OK]   \033[0m[ls | cat | wc | NEWLINE echo]\n");
	else
	{
		printf("\033[31m[FAIL] \033[0m[ls | cat | wc | NEWLINE echo]\n");
	}
}
