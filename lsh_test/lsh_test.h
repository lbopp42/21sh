/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 10:25:37 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/05 09:51:24 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSH_TEST_H
# define LSH_TEST_H

#include "lsh.h"

typedef struct	s_tok_test
{
	int		type;
	char	*content;
}				t_tok_test;

t_token	*test_lexer1(int *nb_tok[], int curs);
t_token	*test_lexer2(int *nb_tok[], int curs);
t_token	*test_lexer3(int *nb_tok[], int curs);
t_token	*test_lexer4(int *nb_tok[], int curs);
t_token	*test_lexer5(int *nb_tok[], int curs);
t_token	*test_lexer6(int *nb_tok[], int curs);
t_token	*test_lexer7(int *nb_tok[], int curs);
t_token	*test_lexer8(int *nb_tok[], int curs);

void	test_parser1(t_token *tok_lst, int nb_tok);
void	test_parser2(t_token *tok_lst, int nb_tok);
void	test_parser3(t_token *tok_lst, int nb_tok);
void	test_parser4(t_token *tok_lst, int nb_tok);
void	test_parser5(t_token *tok_lst, int nb_tok);
void	test_parser6(t_token *tok_lst, int nb_tok);
void	test_parser7(t_token *tok_lst, int nb_tok);
void	test_parser8(t_token *tok_lst, int nb_tok);

#endif
