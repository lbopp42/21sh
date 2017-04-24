/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/24 10:42:08 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isseparator_op(t_token **tok_lst, int nb_tok, int *max)
{
	printf("On entre [isseparator_op]\n");
	(void)nb_tok;
	if (*tok_lst && (*tok_lst)->type == SEMICOLON)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	/*else if ((*tok_lst)->type == AND)
	{
		*pos += 1;
		*tok_lst = *tok_lst->next;
		return (1);
	}*/
	printf("On sort a la fin [isseparator_op]\n");
	return (0);
}

int	isio_file(t_token **tok_lst, int nb_tok, int *max)
{
	if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == LESS &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == LESSAND &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == GREAT &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == GREATAND &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == DGREAT &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	return (0);
}

int	isio_redirect(t_token **tok_lst, int nb_tok, int *max)
{
	if (isio_file(tok_lst, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == IO_NUMBER &&
			isio_file(&(*tok_lst)->next, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 1 && (*tok_lst)->type == DLESS &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i > 2 && (*tok_lst)->type == IO_NUMBER &&
			(*tok_lst)->next->type == DLESS && (*tok_lst)->next->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	return (0);
}

int	iscmd_prefix(t_token **tok_lst, int nb_tok, int mode, int *max)
{
	static int	i = 0;

	if (mode == 1)
		i = 0;
	i++;
	if (isio_redirect(tok_lst, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - (*tok_lst)->i - 2 * i - (i - 1) >= 0 &&
			iscmd_prefix(tok_lst, nb_tok, 2, max) &&
			isio_redirect(&(*tok_lst)->next, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	return (0);
}

int	iscommand(t_token **tok_lst, int nb_tok, int *max)
{
	(void)tok_lst;
	(void)nb_tok;
	(void)max;
	printf("On entre [iscommand]\n");
	//printf("On est au token -> %s\n", (*tok_lst)->content);
	printf("Result here = %d\n", nb_tok - 1 - (*tok_lst)->i);
	printf("Pas de segault jusque la\n");
	if (nb_tok - 1 - (*tok_lst)->i > 2 && iscmd_prefix(tok_lst, nb_tok, 1, max) &&
			(*tok_lst)->next->type == WORD &&
			iscmd_prefix(&(*tok_lst)->next->next, nb_tok, 1, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - 1 - (*tok_lst)->i > 1 && iscmd_prefix(tok_lst, nb_tok, 1, max) &&
			(*tok_lst)->next->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (iscmd_prefix(tok_lst, nb_tok, 1, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if (nb_tok - 1 - (*tok_lst)->i > 1 && (*tok_lst)->type == WORD &&
			iscmd_prefix(&(*tok_lst)->next, nb_tok, 1, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	else if ((*tok_lst)->type == WORD)
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	return (0);
}

int	ispipe_sequence(t_token **tok_lst, int nb_tok, int mode, int *max)
{
	static int	i = 0;

	printf("On entre [ispipe_sequence]\n");
	if (mode == 1)
		i = 0;
	i++;
	printf("\nI = %d\n", i);
	printf("Que vaut le result = %d\n", nb_tok - (*tok_lst)->i - 3 * i - (i - 1));
	if (nb_tok - (*tok_lst)->i - 3 * i - (i - 1) >= 0 &&
			ispipe_sequence(tok_lst, nb_tok, 2, max) &&
			(*tok_lst)->next->type == PIPE)
	{
		printf("On entre ici !\n");
		printf("TEST = %d\n", nb_tok - (*tok_lst)->i - 4 * i - (i - 1));
		if (((nb_tok - (*tok_lst)->i - 4 * i - (i - 1) >= 0 && (*tok_lst)->next->next->type == NEWLINE &&
			iscommand(&(*tok_lst)->next->next->next, nb_tok, max)) ||
		nb_tok - (*tok_lst)->i - 3 * i - (i - 1) >= 0) && iscommand(&(*tok_lst)->next->next, nb_tok, max))
		{
			printf("On entre la\n");
			if ((*tok_lst)->i > *max)
				*max = (*tok_lst)->i;
			return (1);
		}
		else
		{
			printf("Ou on rentre\n");
			return (0);
		}
	}
	else if (printf("ICI AVANT mode = %d\n", mode) && (iscommand(tok_lst, nb_tok, max)/* && i > 1) ||
			(iscommand(tok_lst, nb_tok, max) && i == 1 && !(*tok_lst)->next)*/))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		printf("Je VOUS BAISE\n");
		return (1);
	}
	printf("On sort a la fin de ispipe_sequence avec i = %d\n", i);
	return (0);
}

int	isand_or(t_token **tok_lst, int nb_tok, int *max)
{
	printf("On entre [isand_or]\n");
	if (ispipe_sequence(tok_lst, nb_tok, 1, max))
	{
		printf("On sort [isand_or] qui vaut 1\n");
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		return (1);
	}
	printf("On sort a la fin de [isand_or]\n");
	return (0);
}

int	islist(t_token **tok_lst, int nb_tok, int mode, int *max)
{
	static int	i = 0;

	if (mode == 1)
		i = 0;
	printf("On entre [islist] avec mode = %d\n", mode);
	i++;
	if (nb_tok - (*tok_lst)->i - 3 * i - (i - 1) >= 0 &&
			islist(tok_lst, nb_tok, 2, max) &&
			isseparator_op(&(*tok_lst)->next, nb_tok, max) &&
			isand_or(&(*tok_lst)->next->next, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		printf("On sort de islist avec 1\n");
		return (1);
	}
	else if (printf("ICI C'est BON !\n") && isand_or(tok_lst, nb_tok, max))
	{
		if ((*tok_lst)->i > *max)
			*max = (*tok_lst)->i;
		printf("On sort de islist avec 1\n");
		return (1);
	}
	printf("On sort islist a la fin\n");
	return (0);
}

int	iscomplete_command(t_token **tok_lst, int nb_tok)
{
	int	max;
	int	valid;

	valid = 0;
	max = 0;
	if (islist(tok_lst, nb_tok, 1, &max) && isseparator_op(&(*tok_lst)->next, nb_tok, &max))
	{
		if ((*tok_lst)->i > max)
			max = (*tok_lst)->i;
		printf("On sort [iscomplete_commmand] max vaut %d\n", max);
		valid = 1;
	}
	else if (printf("===============================\nMAINTENANT ON Y EST !\n") && islist(tok_lst, nb_tok, 1, &max))
	{
		if ((*tok_lst)->i > max)
			max = (*tok_lst)->i;
		printf("On sort [iscomplete_commmand] max vaut %d\n", max);
		valid = 1;
	}
	printf("On sort a la fin de [iscomplete_commmand]\n");
	if (valid && max == nb_tok - 1)
		return (1);
	else
		return (0);
}

int main(void)
{
	int		nb_token;
	t_token	*tok_lst;

	nb_token = 3;
	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->i = 0;
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->i = 1;
	tok_lst->next->type = PIPE;
	tok_lst->next->content = ft_strdup("|");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->i = 2;
	tok_lst->next->next->type = WORD;
	tok_lst->next->next->content = ft_strdup("cat");
	tok_lst->next->next->next = NULL;/*(t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->i = 3;
	tok_lst->next->next->next->type = PIPE;
	tok_lst->next->next->next->content = ft_strdup("|");
	tok_lst->next->next->next->next = NULL;*/
	printf("resultat = %d\n", iscomplete_command(&tok_lst, nb_token));
}
