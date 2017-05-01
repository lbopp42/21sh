/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 10:21:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/01 13:03:34 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include "lsh_test.h"

void	launch_test_lexer_from_1_to_25(t_token **array, int *i, int	**nb_tok)
{
	array[*i] = test_lexer1(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer2(nb_tok, *i);
	*i += 1;
}

void	launch_test_parser_from_1_to_25(t_token **array, int *nb_tok)
{
	int i;

	i = 0;
	(void)array;
	(void)nb_tok;
	//test_parser1(array[i], nb_tok[i]);
	i += 1;
	test_parser2(array[i], nb_tok[i]);
}

int	main(void)
{
	t_token	*array[2];
	int		*nb_tok;
	int		i;

	i = 0;
	nb_tok = (int*)ft_memalloc(sizeof(int) * 2);
	printf("\n\033[36m=========  Testing lexer of lsh  =========\n\n\033[0m");
	launch_test_lexer_from_1_to_25(array, &i, &nb_tok);
	printf("\n\033[36m=========    End of lexer test   =========\n\n\033[0m");
	printf("\n\033[36m=========  Testing parser of lsh  =========\n\n\033[0m");
	launch_test_parser_from_1_to_25(array, nb_tok);
}
