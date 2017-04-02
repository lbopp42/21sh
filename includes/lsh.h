/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/04/02 16:43:55 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSH_H
# define LSH_H

char	*g_line;

#include "libft.h"
#include <stdio.h>

enum {
	SEMICOLON = 0,
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	OUTPUT,
	INPUT,
	WORD,
	QUOTE,
	DQUOTE,
	BQUOTE,
};

typedef struct	s_state
{
	int				state;
	struct s_state	*next;
}				t_state;
typedef struct	s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;

void	print_lst(t_token *tok_lst);
void	print_state_lst(t_state *state_lst);

int		isop(int *i);
int		isquote(int *i);
void	fill_tok_lst(t_token **tok_lst, t_state **state_lst);
int		find_type(int *i);
t_state	*get_last_state(t_state *state_lst);
t_token	*get_last_token(t_token *tok_lst);
void	state_management(t_state **state_lst, int *i);
void	token_management(t_token **t_lst, t_state *s_lst, int *i, int type);

#endif
