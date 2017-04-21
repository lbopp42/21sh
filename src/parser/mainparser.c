/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 13:45:55 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/21 17:02:03 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int	isseparator_op(t_token **tok_lst, int *pos);

int	isio_file(t_token **tok_lst, int nb_tok, int *pos)
{
	printf("On entre dans isio_file\n");
	if (nb_tok - *pos > 1 && (*tok_lst)->type == LESS && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - *pos > 1 && (*tok_lst)->type == LESSAND && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - *pos> 1 && (*tok_lst)->type == GREAT && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - *pos> 1 && (*tok_lst)->type == GREATAND && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - *pos> 1 && (*tok_lst)->type == DGREAT && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	printf("On sort de isio_file\n");
	return (0);
}

int	isio_redirect(t_token **tok_lst, int nb_tok, int *pos)
{
	printf("On entre dans isio_redirect\n");
	printf("On a %s\n", (*tok_lst)->content);
	printf("test here = %d\n", nb_tok - *pos);
	printf("pos = %d\n", *pos);
	if (isio_file(tok_lst, nb_tok, pos))
		return (1);
	else if (nb_tok - *pos > 1 && (*tok_lst)->type == IO_NUMBER && isio_file(&(*tok_lst)->next, nb_tok, pos))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	else if (nb_tok - *pos > 1 && (*tok_lst)->type == DLESS && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next;
		*pos += 2;
		return (1);
	}
	else if (nb_tok - * pos > 2 && (*tok_lst)->next->next &&
			(*tok_lst)->type == IO_NUMBER && (*tok_lst)->next->type == DLESS &&
			(*tok_lst)->next->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next->next->next;
		*pos += 3;
		return (1);
	}
	printf("On sort de isio_redirect\n");
	return (0);
}

int	iscmd_prefix(t_token **tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	printf("On entre dans iscmd_prefix\n");
	if (isio_redirect(tok_lst, nb_tok, pos))
		return (1);
	else if (nb_tok - *pos > 1 && (nb_tok - *pos - 2 * i - i - 1) >= 0 && iscmd_prefix(tok_lst, nb_tok, pos) &&
			isio_redirect(&(*tok_lst)->next, nb_tok, pos))
		return (1);
	printf("On sort de iscmd_prefix\n");
	return (0);
}

int	iscommand(t_token **tok_lst, int nb_tok, int *pos, int add_pos)
{
	printf("On entre dans iscommand\n");
	*pos += add_pos;
	(void)tok_lst;
	(void)nb_tok;
	printf("test pos = %d\n", nb_tok - *pos);
	if (nb_tok - *pos > 2 && iscmd_prefix(tok_lst, nb_tok, pos) && (*tok_lst)->next->type == WORD &&
			iscmd_prefix(&(*tok_lst)->next->next, nb_tok, pos))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		printf("CELUI LA\n");
		return (1);
	}
	else if (nb_tok - *pos > 1 && iscmd_prefix(tok_lst, nb_tok, pos) && (*tok_lst)->next->type == WORD)
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		printf("CELUI  OU LA\n");
		return (1);
	}
	else if (iscmd_prefix(tok_lst, nb_tok, pos))
		return (1);
	else if (nb_tok - *pos > 1 && (*tok_lst)->type == WORD && iscmd_prefix(&(*tok_lst)->next, nb_tok, pos))
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		printf("CELUI  ET T TERTLA\n");
		return (1);
	}
	else if ((*tok_lst)->type == WORD)
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		printf("ON SRT LA\n");
		return (1);
	}
	return (0);
}

int	ispipe_sequence(t_token **tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	printf("On entre dans ispipe_sequence\n");
	printf("On est la [%s]\n", (*tok_lst)->content);
	printf("nb_tok = %d\n", nb_tok);
	printf("pos result = %d\n", (nb_tok - *pos - 4 * i - i - 1) >= 0);
	printf("pipe  = %d, result = %d\n", PIPE, (*tok_lst)->next->type);
	printf("test = %s\n", (*tok_lst)->next->next->content);
	//printf("iscommand  = %d\n", iscommand(&(*tok_lst)->next->next, nb_tok, pos, 2));
	if (nb_tok - *pos > 2 && (nb_tok - *pos - 4 * i - i - 1) >= 0 && ispipe_sequence(tok_lst, nb_tok, pos) &&
			(*tok_lst)->next->type == PIPE && (((*tok_lst)->next->next->type == NEWLINE &&
					iscommand(&(*tok_lst)->next->next->next, nb_tok, pos, 3)) ||
					iscommand(&(*tok_lst)->next->next, nb_tok, pos, 2)))
		return (1);
	else if (iscommand(tok_lst, nb_tok, pos, 0))
		return (1);
	return (0);
}

int	isand_or(t_token **tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	printf("On entre dans isand_or\n");
	/*if ((nb_tok - *pos - 4 * i - i - 1) >= 0 && isand_or(tok_lst) && tokenx + 1 == "&&" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)))
		return (1);
	else if ((nb_tok - *pos - 4 * i - i - 1) >= 0 && isand_or(tokenx) && tokenx + 1 == "||" && ((tokenx + 2 == '\n' && ispipe_sequence(tokenx + 3)) || ispipe_sequence(tokenx + 2)))
		return (1);
	else */if (ispipe_sequence(tok_lst, nb_tok, pos))
		return (1);
	return (0);
}

int	islist(t_token **tok_lst, int nb_tok, int *pos)
{
	static int i = 0;

	i++;
	printf("On entre dans islist\n");
	if (nb_tok - *pos > 2 && (nb_tok - *pos - 3 * i - i - 1) >= 0 && islist(tok_lst, nb_tok, pos) &&
			isseparator_op(&(*tok_lst)->next, pos) && isand_or(&(*tok_lst)->next->next, nb_tok, pos))
		return (1);
	else if (isand_or(tok_lst, nb_tok, pos))
		return (1);
	return (0);
}

int	isseparator_op(t_token **tok_lst, int *pos)
{
	if ((*tok_lst)->type == SEMICOLON)
	{
		*tok_lst = (*tok_lst)->next;
		*pos += 1;
		return (1);
	}
	/*else if (tok_lst == '&')
		return (1);*/
	return (0);
}

int	iscomplete_command(t_token **tok_lst, int nb_tok)
{
	int	pos;

	pos = 0;
	printf("On entre dans iscomplete_command\n");
	if (islist(tok_lst, nb_tok, &pos))
		return (1);
	else if (nb_tok > 1 && islist(tok_lst, nb_tok, &pos) && isseparator_op(&(*tok_lst)->next, &pos))
		return (1);
	return (0);
}

int main(void)
{
	int		nb_token;
	t_token	*tok_lst;

	printf("TEST\n");
	tok_lst = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->type = WORD;
	tok_lst->content = ft_strdup("ls");
	tok_lst->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->type = PIPE;
	tok_lst->next->content = ft_strdup("|");
	tok_lst->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->type = PIPE;
	tok_lst->next->next->content = ft_strdup("|");
	/*tok_lst->next->next->next = (t_token*)ft_memalloc(sizeof(t_token));
	tok_lst->next->next->next->type = WORD;
	tok_lst->next->next->next->content = ft_strdup("cat");*/
	tok_lst->next->next->next = NULL;
	nb_token = 3;
	printf("TEST\n");
	printf("resultat = %d\n", iscomplete_command(&tok_lst, nb_token));
	printf("RESTE = %s\n", tok_lst->content);
}
