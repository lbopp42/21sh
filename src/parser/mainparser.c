/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/23 11:07:55 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isseparator_op(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	(void)nb_tok;
	(void)pos_tmp;
	if ((*tok_lst)->type == SEMICOLON)
	{
		*pos += 1;
		*tok_lst = (*tok_lst)->next;
		return (1);
	}
	/*else if ((*tok_lst)->type == AND)
	{
		*pos += 1;
		*tok_lst = *tok_lst->next;
		return (1);
	}*/
	return (0);
}

int	isio_file(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == LESS &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == LESSAND &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == GREAT &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == GREATAND &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == DGREAT &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	return (0);
}

int	isio_redirect(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	if (isio_file(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == IO_NUMBER &&
			isio_file(&(*tok_lst)->next, nb_tok, pos, pos_tmp + 1))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == DLESS &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - *pos > 2 && (*tok_lst)->type == IO_NUMBER &&
			(*tok_lst)->next->type == DLESS && (*tok_lst)->next->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next->next;
		*pos += 3;
		return (1);
	}
	return (0);
}

int	iscmd_prefix(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	static int	i = 0;

	i++;
	if (isio_redirect(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	else if (nb_tok - pos_tmp - 2 * i - i - 1 >= 0 &&
			iscmd_prefix(tok_lst, nb_tok, pos, pos_tmp) &&
			isio_redirect(&(*tok_lst)->next, nb_tok, pos, pos_tmp + 1))
		return (1);
	return (0);
}

int	iscommand(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	if (nb_tok - pos_tmp > 2 && iscmd_prefix(tok_lst, nb_tok, pos, pos_tmp) &&
			(*tok_lst)->next->type == WORD &&
			iscmd_prefix(&(*tok_lst)->next->next, nb_tok, pos, pos_tmp + 2))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	else if (nb_tok - pos_tmp > 1 && iscmd_prefix(tok_lst, nb_tok, pos, pos_tmp) &&
			(*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	else if (iscmd_prefix(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	else if (nb_tok - pos_tmp > 1 && (*tok_lst)->type == WORD &&
			iscmd_prefix(&(*tok_lst)->next, nb_tok, pos, pos_tmp + 1))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	else if ((*tok_lst)->type == WORD)
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	return (0);
}

int	ispipe_sequence(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	static int	i = 0;

	i++;
	if (nb_tok - pos_tmp - 4 * i - i - 1 >= 0 &&
			ispipe_sequence(tok_lst, nb_tok, pos, pos_tmp) &&
			(*tok_lst)->next->type == PIPE &&
			(((*tok_lst)->next->next->type == NEWLINE &&
			iscommand(&(*tok_lst)->next->next->next, nb_tok, pos, pos_tmp + 3)) ||
		iscommand(&(*tok_lst)->next->next, nb_tok, pos, pos_tmp + 2)))
			return (1);
	else if (iscommand(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	return (0);
}

int	isand_or(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	if (ispipe_sequence(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	return (0);
}

int	islist(t_token **tok_lst, int nb_tok, int *pos, int pos_tmp)
{
	static int	i = 0;

	i++;
	if (nb_tok - pos_tmp - 3 * i - i - 1 >= 0 &&
			islist(tok_lst, nb_tok, pos, pos_tmp) &&
			isseparator_op(&(*tok_lst)->next, nb_tok, pos, pos_tmp + 1) &&
			isand_or(&(*tok_lst)->next->next, nb_tok, pos, pos_tmp + 2))
		return (1);
	else if (isand_or(tok_lst, nb_tok, pos, pos_tmp))
		return (1);
	return (0);
}

int	iscomplete_command(t_token **tok_lst, int nb_tok)
{
	int	pos;
	int	pos_tmp;

	pos = 0;
	pos_tmp = 0;
	if (islist(tok_lst, nb_tok, &pos, pos_tmp) &&
			isseparator_op(&(*tok_lst)->next, nb_tok, &pos, pos_tmp + 1))
		return (1);
	else if (islist(tok_lst, nb_tok, &pos, pos_tmp))
		return (1);
	return (0);
}

int main(void)
{
	int		nb_token;
	t_token	*tok_lst;

	nb_token = 1;
	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = NULL;
	printf("resultat = %d\n", iscomplete_command(&tok_lst, nb_token));
}
