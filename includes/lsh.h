/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 11:11:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSH_H
# define LSH_H

char	*g_line;
char	**g_env;

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
	ASSIGNMENT_WORD,
	NEWLINE,
	IO_NUMBER,
	BLANK,
};

typedef struct	s_ast_node
{
	int					type;
	char				*content;
	struct s_ast_node	*right;
	struct s_ast_node	*left;
}				t_ast_node;

typedef struct	s_tuple
{
	int					mv;
	struct s_ast_node	*ast_tree;
}				t_tuple;

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

int		execution(t_ast_node *ast_tree, char **env);
char	*here_doc(char *delimiter, int option);
void	main_expand(t_ast_node **ast_tree);

/* ************************ */
/*			BUILTINS		*/
/* ************************ */

void	ft_setenv(char **cmd);
void	ft_unsetenv(char **cmd);
char	**list_to_tab(t_lst *lst);
t_lst	*tab_to_list(char *array[]);


void	add_to_current_tok(t_token **tok_lst, int i, int type);
int		big_op(char *content, int i);
void	create_new_token(t_token **tok_lst, int i, int type);
void	create_new_token_next(t_token **tok_lst, int i, int type);
t_tuple	*iscomplete_cmd(t_token *tok_lst, int nb_tok, int mv);
int		is_digit_token(char *content);
int		is_piece_of_bigop(t_token **tok_lst, t_state **st_lst, int *sp, int i);
int		is_new_op(int i);
int		lexer_posix(t_token **tok_lst, t_state **st_lst);
void	state_management(t_state **st_lst, char c);
int		treatment_of_quote(t_token **tok_lst, t_state **st_lst, int *sp, int i);
int		treatment_of_old_word(t_token **tok_lst, int *sp, int i);
int		treatment_of_new_word(t_token **tok_lst, int *sp, int i);
int		treatment_newline(t_token **tok_lst, int i, int type);
int		treatment_new_op(t_token **tok_lst, int *sp, int i, int type);

#endif
