/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:10:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/24 14:42:32 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isio_file(t_token *tok_lst, int nb_tok, int *max)
{
	(void)nb_tok;
	if (tok_lst->type == LESS && tok_lst->next->type == WORD)
	{
		if (tok_lst->next->i > *max)
			*max = tok_lst->next->i;
			return (1);
	}
	else if (tok_lst->type == LESSAND && tok_lst->next->type == WORD)
	{
		if (tok_lst->next->i > *max)
			*max = tok_lst->next->i;
			return (1);
	}
	else if (tok_lst->type == GREAT && tok_lst->next->type == WORD)
	{
		printf("ON SORT ICI HIHI, i = %d\n", tok_lst->next->i);
		if (tok_lst->next->i > *max)
			*max = tok_lst->next->i;
			return (1);
	}
	else if (tok_lst->type == GREATAND && tok_lst->next->type == WORD)
	{
		if (tok_lst->next->i > *max)
			*max = tok_lst->next->i;
			return (1);
	}
	else if (tok_lst->type == DGREAT && tok_lst->next->type == WORD)
	{
		if (tok_lst->next->i > *max)
			*max = tok_lst->next->i;
			return (1);
	}
	return (0);
}

/*
**	nb_tok - tok_lst->i >= 2:
**	This is use to check if we have enought token to use the function
*/

int	isio_redirect(t_token *tok_lst, int nb_tok, int *max)
{
	if (nb_tok - tok_lst->i >= 2 && isio_file(tok_lst, nb_tok, max))
	{
		printf("OU ICI\n");
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			isio_file(tok_lst->next, nb_tok, max))
	{
		printf("OU LA\n");
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (tok_lst->type == DLESS && tok_lst->next &&
			tok_lst->next->type == WORD)
	{
		printf("ICI voila\n");
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (tok_lst->type == IO_NUMBER && tok_lst->next &&
			tok_lst->next->type == DLESS && tok_lst->next->next &&
			tok_lst->next->next->type == WORD)
	{
		printf("A NON La\n");
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	return (0);
}

/*
**	The static [i] is here to avoid an infinity loop
**	2 * i - (i - 1) : this is to avoid an infinity loop too
**	-> It will begin with 2 and increase 1 by 1
*/

int	iscmd_prefix(t_token *tok_lst, int nb_tok, int *max)
{
	static int i = -1;

	i++;
	if (nb_tok - tok_lst->i >= 2 * i - (i - 1) && iscmd_prefix(tok_lst, nb_tok, max) &&
			tok_lst->next && isio_redirect(tok_lst->next, nb_tok, max))
	{
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (isio_redirect(tok_lst, nb_tok, max))
	{
		printf("ON PASSE LA\n");
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	return (0);
}

int	is_simplecmd(t_token *tok_lst, int nb_tok, int *max)
{
	if (iscmd_prefix(tok_lst, nb_tok, max) && tok_lst->next &&
			tok_lst->next->type == WORD && tok_lst->next->next &&
			iscmd_prefix(tok_lst->next->next, nb_tok, max))
	{
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (printf("ON PASSE\n") && iscmd_prefix(tok_lst, nb_tok, max) && tok_lst->next->type &&
			tok_lst->next->type == WORD)
	{
		printf("C'est bien la, et i = %d\n", tok_lst->next->i);
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (iscmd_prefix(tok_lst, nb_tok, max))
	{
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (tok_lst->type == WORD && tok_lst->next &&
			iscmd_prefix(tok_lst->next, nb_tok, max))
	{
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	else if (tok_lst->type == WORD)
	{
		if (tok_lst->i > *max)
			*max = tok_lst->i;
			return (1);
	}
	return (0);
}
