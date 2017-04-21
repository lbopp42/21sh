/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/21 10:43:04 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isio_file(tokenx)
{
	if (tokenx == '<' && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == "<&" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == '>' && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == ">&" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == ">>" && tokenx + 1 == WORD)
		return (1);
	return (0);
}

int	isio_redirect(tokenx)
{
	if (isio_file(tokenx))
		return (1);
	else if (tokenx == IO_NUMBER && isiofile(tokenx + 1))
		return (1);
	else if (tokenx == "<<" && tokenx + 1 == WORD)
		return (1);
	else if (tokenx == IO_NUMBER && tokenx + 1 == "<<")
		return (1);
	return (0);
}

int	iscmd_prefix(tokenx)
{
	static int i = 0;

	i++;
	if (isio_redirect(tokenx))
		return (1);
	else if (iscmd_prefix(tokenx) && isio_redirect(tokenx + 1) && i < 2)
		return (1);
	return (0);
}

int	iscommand(tokenx)
{
	if (iscmd_prefix(tokenx) && tokenx + 1 == WORD && iscmd_prefix(tokenx + 2))
		return (1);
	else if (iscmd_prefix(tokenx) && tokenx + 1 == WORD)
		return (1);
	else if (iscmd_prefix(tokenx))
		return (1);
	else if (tokenx == WORD && iscmd_prefix(tokenx + 1))
		return (1);
	else if (token == WORD)
		return (1);
	return (0);
}

int	ispipe_sequence(t_token *tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	if ((nb_tok - *pos - 4 * i - i - 1) >= 0 && ispipe_sequence(tok_lst) &&
			tok_lst->next->type == PIPE && ((tok_lst->next->next->type == NEWLINE &&
					iscommand(tok_list->next->next->next, pos) || iscommand(tok_lst->next->next, pos))))
		return (1);
	else if (iscommand(tok_lst, pos))
		return (1);
	return (0);
}

int	isand_or(t_token *tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	/*if ((nb_tok - *pos - 4 * i - i - 1) >= 0 && isand_or(tok_lst) && tokenx + 1 == "&&" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)))
		return (1);
	else if ((nb_tok - *pos - 4 * i - i - 1) >= 0 && isand_or(tokenx) && tokenx + 1 == "||" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)))
		return (1);
	else */if (ispipe_sequence(tok_lst, nb_tok, pos))
		return (1);
	return (0);
}

int	islist(t_token *tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	if ((nb_tok - *pos - 3 * i - i - 1) >= 0 && islist(tok_lst, nb_tok, *pos) &&
			isseparator_op(tok_lst->next, pos) && isand_or(token_lst->next->next, nb_tok, pos))
		return (1);
	else if (isand_or(token_lst->next->next, nb_tok, pos))
		return (1);
	return (0);
}

int	isseparator_op(t_token *tok_lst, int *pos)
{
	if (tok_lst->type == SEMICOLON)
		return (1);
	/*else if (tok_lst == '&')
		return (1);*/
	return (0);
}

int	iscomplete_command(t_token *tok_lst, int nb_tok)
{
	int	pos;

	pos = 0;
	if (islist(tok_lst, nb_tok, &pos))
		return (1);
	else if (islist(tok_lst, nb_tok, &pos) && isseparator_op(tok_lst->next, nb_tok, &pos))
		return (1);
	return (0);
}

int main(void)
{
	int		nb_token;
	t_token	*tok_lst = {};

	nb_token = 10;
	iscomplete_command(tok_lst, nb_token);
}
