/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/05/10 10:06:07 by lbopp            ###   ########.fr       */
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
	GREATAND,
	LESSAND,
	QUOTE,
	DQUOTE,
	BQUOTE,
	WORD,
	NEWLINE,
	IO_NUMBER,
	BLANK,
};

typedef struct	s_state
{
	int				state;
	struct s_state	*next;
}				t_state;
typedef struct	s_token
{
	int				i;
	int				type;
	char			*content;
	struct s_token	*next;
}				t_token;

void	add_to_current_tok(t_token **tok_lst, int i, int type);
int		big_op(char *content, int i);
void	create_new_token(t_token **tok_lst, int i, int type);
void	create_new_token_next(t_token **tok_lst, int i, int type);
int		iscomplete_cmd(t_token *tok_lst, int nb_tok, int mv);
int		is_digit_token(char *content);
int		is_piece_of_bigop(t_token **tok_lst, t_state **st_lst, int *sp, int i);
int		is_new_op(int i);
int		lexer_posix(t_token **tok_lst, t_state **st_lst);
void	state_management(t_state **st_lst, int i);
int		treatment_of_quote(t_token **tok_lst, t_state **st_lst, int *sp, int i);
int		treatment_of_old_word(t_token **tok_lst, int *sp, int i);
int		treatment_of_new_word(t_token **tok_lst, int *sp, int i);
int		treatment_newline(t_token **tok_lst, int i, int type);
int		treatment_new_op(t_token **tok_lst, int *sp, int i, int type);

#endif
