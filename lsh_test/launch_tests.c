/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 10:21:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/17 16:43:02 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include "lsh_test.h"
#define NB_TEST 13

void	launch_test_lexer_from_1_to_25(t_token **array, int *i, int	**nb_tok)
{
	array[*i] = test_lexer1(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer2(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer3(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer4(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer5(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer6(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer7(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer8(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer9(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer10(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer11(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer12(nb_tok, *i);
	*i += 1;
	array[*i] = test_lexer13(nb_tok, *i);
}

void	launch_test_parser_from_1_to_25(t_token **array, int *nb_tok)
{
	int i;

	i = 0;
	(void)array;
	(void)nb_tok;
	test_parser1(array[i], nb_tok[i]);
	i += 1;
	test_parser2(array[i], nb_tok[i]);
	i += 1;
	test_parser3(array[i], nb_tok[i]);
	i += 1;
	test_parser4(array[i], nb_tok[i]);
	i += 1;
	test_parser5(array[i], nb_tok[i]);
	i += 1;
	test_parser6(array[i], nb_tok[i]);
	i += 1;
	test_parser7(array[i], nb_tok[i]);
	i += 1;
	test_parser8(array[i], nb_tok[i]);
	i += 1;
	test_parser9(array[i], nb_tok[i]);
	i += 1;
	test_parser10(array[i], nb_tok[i]);
	i += 1;
	test_parser11(array[i], nb_tok[i]);
	i += 1;
	test_parser12(array[i], nb_tok[i]);
	i += 1;
	test_parser13(array[i], nb_tok[i]);
	/*while (array[i])
	{
		printf("content = [%s] et type = [%d]\n", array[i]->content, array[i]->type);
		array[i] = array[i]->next;
	}*/
}

int	main(void)
{
	t_token	*array[NB_TEST];
	int		*nb_tok;
	int		i;

	i = 0;
	nb_tok = (int*)ft_memalloc(sizeof(int) * NB_TEST);
	printf("\n\033[36m=========  Testing lexer of lsh  =========\n\n\033[0m");
	launch_test_lexer_from_1_to_25(array, &i, &nb_tok);
	printf("\n\033[36m=========    End of lexer test   =========\033[0m");
	printf("\n\033[36m=========  Testing parser of lsh  =========\n\n\033[0m");
	launch_test_parser_from_1_to_25(array, nb_tok);
	printf("\n\033[36m=========    End of parser test   =========\033[0m\n");
}
