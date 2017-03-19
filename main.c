/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 10:28:01 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/19 13:03:04 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		isinstrarray(char *cmp, const char *tok_lst[])
{
	int			i;
	int			max;
	int			ret;

	i = 0;
	max = 0;
	ret = -1;
	while (tok_lst[i])
	{
		if (!ft_strncmp(cmp, tok_lst[i], ft_strlen(tok_lst[i])))
		{
			max = max < ft_strlen(tok_lst[i]) ? ft_strlen(tok_lst[i]) : max;
			ret = i;
		}
		i++;
	}
	return (ret);
}

void	get_token(void)
{
	char		current_tok[256];
	int			i;
	int			id_tok;
	const char	*tok_lst[9] = {";", "|", "<", "<<", ">", ">>", "<&", ">&", NULL};
	int			tmp;

	i = 0;
	id_tok = 0;
	tmp = 0;
	ft_bzero(current_tok, 256);
	while (g_line[i])
	{
		if ((tmp = isinstrarray(&g_line[i], tok_lst)) >= 0)
		{
			if (current_tok[0])
				printf("TOKEN = %s\n", current_tok);
			ft_bzero(current_tok, ft_strlen(current_tok));
			id_tok = 0;
			printf("TOKEN = %s\n", tok_lst[tmp]);
			i += ft_strlen(tok_lst[tmp]) - 1;
		}
		else if (ft_isspace(g_line[i]))
		{
			if (current_tok[0])
				printf("TOKEN = %s\n", current_tok);
			ft_bzero(current_tok, ft_strlen(current_tok));
			id_tok = 0;
		}
		else
		{
			current_tok[id_tok] = g_line[i];
			id_tok++;
		}
		i++;
	}
	if (current_tok[0])
		printf("TOKEN = %s\n", current_tok);

}

int		main(int ac, char *av[])
{
	g_line = NULL;
	get_next_line(0, &g_line);
	get_token();
	return (1);
}
