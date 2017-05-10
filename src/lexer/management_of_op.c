/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_of_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:26:46 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/10 09:46:41 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

int		big_op(char *content, int i)
{
	char		tmp[3];
	int			curs;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	curs = 0;
	tmp[0] = content[0];
	tmp[1] = g_line[i];
	tmp[2] = '\0';
	while (token[curs])
	{
		if (ft_strequ((const char*)tmp, (const char*)token[curs]))
			return (curs);
		curs += 1;
	}
	return (WORD);
}

int		is_new_op(int i)
{
	int			id;
	const char	*token[9] = {";", "|", "<", ">", "<<", ">>", ">&", "<&", NULL};

	id = 0;
	while (token[id])
	{
		if (g_line[i] == token[id][0])
			return (id);
		id++;
	}
	return (WORD);
}

int		treatment_new_op(t_token **tok_lst, int *sp, int i, int type)
{
	*sp = 0;
	if (*tok_lst)
	{
		if ((type == GREAT || type == LESS) &&
				is_digit_token((*tok_lst)->content))
			(*tok_lst)->type = IO_NUMBER;
		create_new_token_next(tok_lst, i, type);
		return (2);
	}
	else
		create_new_token(tok_lst, i, type);
	return (1);
}
