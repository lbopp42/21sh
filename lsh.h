/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/23 13:21:26 by lbopp            ###   ########.fr       */
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
	BLANK
};

typedef struct	s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;

#endif
