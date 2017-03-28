/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/28 10:06:35 by lbopp            ###   ########.fr       */
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
	QUOTE,
	DQUOTE,
	BQUOTE,
	WORD,
	BLANK
};

typedef struct	s_state
{
	int				state;
	struct s_state	*next;
}				t_state;
typedef struct	s_stat_array
{
	int	current_state;
	int	ret_funct;
	int	next_state;
}				t_stat_array;
typedef struct	s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;

void	print_lst(t_token *tok_lst);
void	get_token(t_token **tok_lst, t_state **state_lst);

#endif
