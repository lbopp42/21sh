/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 11:10:32 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/15 15:11:32 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser1(t_token *tok_lst, int nb_tok)
{
	t_tuple	*tmp;

	tmp = iscomplete_cmd(tok_lst, nb_tok, 0);
	if (nb_tok == tmp->mv)
		printf("\033[32m[OK]   \033[0m[ls]\n");
	else
		printf("\033[31m[FAIL] \033[0m[ls]\n");
}
