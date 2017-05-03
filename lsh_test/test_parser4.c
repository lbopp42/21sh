/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 10:14:19 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/03 10:15:31 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh_test.h"

void	test_parser4(t_token *tok_lst, int nb_tok)
{
	if (nb_tok == iscomplete_cmd(tok_lst, nb_tok, 0))
		printf("\033[32m[OK]   \033[0m[echo \"ls ; `cat`\"\"test2\"]\n");
	else
		printf("\033[31m[FAIL] \033[0m[echo \"ls ; `cat`\"\"test2\"]\n");
}
