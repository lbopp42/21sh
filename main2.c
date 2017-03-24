/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 10:28:01 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/21 15:02:07 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		isinstrarray(char *cmp, const char *tok_lst[])
{
	int			i;
	size_t		max;
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

void	put_token_in_lst(t_token **tok_lst, char *token, int type)
{
	t_token		*tmp;

	tmp = *tok_lst;
	if (!*tok_lst)
	{
		if (!(*tok_lst = (t_token*)ft_memalloc(sizeof(t_token))))
			return ;
		(*tok_lst)->type = type;
		(*tok_lst)->content = ft_strdup(token);
		(*tok_lst)->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_token*)ft_memalloc(sizeof(t_token))))
			return ;
		tmp->next->type = type;
		tmp->next->content = ft_strdup(token);
		tmp->next->next = NULL;
	}
	return ;
}

void	print_lst(t_token *tok_lst)
{
	t_token	*tmp;
	char	*test[] = {"SEMICOLON", "PIPE", "LESS", "DLESS", "GREAT", "DGREAT",
	"INPUT", "OUTPUT", "WORD", "BLANK"};

	tmp = tok_lst;
	while (tmp)
	{
		printf("TOKEN = [%s] and TYPE = %s\n", tmp->content, test[tmp->type]);
		tmp = tmp->next;
	}
}

void	get_token(void)
{
	char		current_tok[256];
	int			i;
	int			id_tok;
	const char	*tok_array[9] = {";", "|", "<", "<<", ">", ">>", "<&", ">&", NULL};
	int			tmp;
	t_token		*tok_lst;

	i = 0;
	id_tok = 0;
	tmp = 0;
	tok_lst = NULL;
	ft_bzero(current_tok, 256);
	while (g_line[i])
	{
		if ((tmp = isinstrarray(&g_line[i], tok_array)) >= 0)
		{
			if (current_tok[0])
				put_token_in_lst(&tok_lst, current_tok, WORD);
			ft_bzero(current_tok, ft_strlen(current_tok));
			id_tok = 0;
			put_token_in_lst(&tok_lst, (char*)tok_array[tmp], tmp);
			i += ft_strlen(tok_array[tmp]) - 1;
		}
		else if (ft_isspace(g_line[i]))
		{
			if (current_tok[0])
				put_token_in_lst(&tok_lst, current_tok, WORD);
			put_token_in_lst(&tok_lst, " ", BLANK);
			while (ft_isspace(g_line[i]))
				i++;
			i--;
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
		put_token_in_lst(&tok_lst, current_tok, WORD);
	print_lst(tok_lst);
}

int		main(void)
{
	g_line = NULL;
	get_next_line(0, &g_line);
	get_token();
	return (1);
}