/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 10:29:20 by lbopp             #+#    #+#             */
/*   Updated: 2017/03/19 14:36:05 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSH_H
# define LSH_H

# include "libft.h"
# include <stdio.h>

typedef struct	s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;
char	*g_line;

#endif
