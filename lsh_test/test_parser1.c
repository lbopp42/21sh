/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 11:10:32 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/01 12:37:27 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser1(t_token *tok_lst, int nb_tok)
{
	if (nb_tok == iscomplete_cmd(tok_lst, nb_tok, 0))
		printf("\033[32m[OK]   \033[0m[ls]\n");
	else
		printf("\033[31m[FAIL] \033[0m[ls]\n");
}
