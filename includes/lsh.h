/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 15:15:33 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/18 14:40:29 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSH_H
# define LSH_H

#include "libft.h"
#include <sys/wait.h>
#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#define READ_END 0
#define WRITE_END 1

enum
{
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
enum
{
	KEY_ENTER,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_DEL,
};
typedef struct	s_heredoc
{
	t_list				*content;
	struct s_heredoc	*next;
}				t_heredoc;
typedef struct	s_ast_node
{
	int					type;
	t_list				*content;
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
typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;
typedef struct	s_lineinfo
{
	int		curs;	//index du contenu
	char	*content;
	t_pos	pos;
	int		p_len;	//taille du prompt
	int		len;
	int		len_max;
	t_pos	select_start;
	int		select_len;
	char	*select;
}				t_lineinfo;
typedef struct	s_list_double
{
	char					*content;
	struct s_list_double	*prev;
	struct s_list_double	*next;
}				t_list_double;

t_lineinfo			*g_linei;
struct termios		g_origin_term;
char				*g_line;
char				**g_env;
int					g_last_status;
t_list_double		*g_history;


int		execution(t_ast_node *ast_tree, char **env);
t_list	*here_doc(char *delimiter, int option);
void	main_expand(t_ast_node **ast_tree);

/* ************************ */
/*			BUILTINS		*/
/* ************************ */

int		exec_cd(char *cmd, int option, t_lst **env);
void	del_array(char *array[]);
void	del_lst(t_lst *lst);
int		ft_cd(char **cmd);
int		ft_echo(char **cmd);
int		ft_env(char **cmd, int in_fork);
int		ft_exit(char **cmd);
int		ft_setenv(char **cmd);
int		ft_unsetenv(char **cmd);
char	**list_to_tab(t_lst *lst);
void	put_in_env(t_lst **env, char *var, char *valeur);
t_lst	*tab_to_list(char *array[]);

/* ************************ */
/*  		 EXPAND			*/
/* ************************ */

char	*get_var_content(char *var_env);
void	launch_expand(t_list **list);

/* ************************ */
/*			PARSER			*/
/* ************************ */

char	**list_to_array(t_list *lst);

/* ************************ */
/*		   EXECUTION	  	*/
/* ************************ */

int		main_exec(t_ast_node *ast_tree, int in_fork, int fd_min);
void	execution_cmd(t_list *content, int in_fork, char *path);

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

/* ************************ */
/*		 LINE EDITING	  	*/
/* ************************ */

void	default_term(void);
char	*editing_line(void);
void	init_term(void);
void	move_to(t_pos tmp_pos);
void	save_reset_pos(t_pos pos, int mode);

/* ************************ */
/*			 HISTORY	  	*/
/* ************************ */

void	add_to_history(char	*line);
void	main_history(void);
void	put_my_str_edit(char *content);
void	save_history(void);

#endif
