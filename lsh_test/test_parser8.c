/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 09:47:21 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 09:56:43 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser8(t_token *tok_lst, int nb_tok)
{
	if (nb_tok == iscomplete_cmd(tok_lst, nb_tok, 0))
		printf("\033[31m[FAIL] \033[0m[ls | cat | wc NEWLINE | echo] [ERROR NOT FOUND]\n");
	else
		printf("\033[32m[OK]   \033[0m[ls | cat | wc NEWLINE | echo] [ERROR FOUND]\n");
}
