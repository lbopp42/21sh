/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 14:17:58 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/23 15:51:32 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include "lsh.h"
#include <sys/ioctl.h>

/*
**	pos is used to know the position of the column at the end of the line.
**	col is used to know the postion of the cursor column.
*/
typedef struct	s_linfo
{
	char	*content;
	int		curs;
	int		len;
	int		pos;
	int		col;
	int		max_len;
}				t_linfo;
struct s_linfo	*g_linei;
struct termios		g_origin_term;
void	default_term(void);

void	init_term()
{
	char			*term;
	struct termios	attr;

	tcgetattr(0, &g_origin_term);
	tcgetattr(0, &attr);
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attr);
	if (!(term = getenv("TERM")))
	{
		ft_putendl_fd("lsh: environment not found", 2);
		default_term();
		exit(0);
	}
	else
		tgetent(NULL, term);
}

void	default_term(void)
{
	tcsetattr(0, TCSADRAIN, &g_origin_term);
	tgetent(NULL, getenv("TERM"));
}

int	put_my_char(int c)
{
	write(1, &c, 1);
	return (1);
}

char	*realloc_char(char **ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = (char*)ft_memalloc(sizeof(char) * size);
	ft_memmove(new_ptr, *ptr, ft_strlen(*ptr));
	//ft_strdel(ptr);
	return (new_ptr);
}

void	add_char_to_line(char c)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->len == g_linei->len)
	{
		g_linei->content = realloc_char(&g_linei->content, g_linei->max_len + 20);
		g_linei->max_len += 20;
	}
	if (g_linei->len == g_linei->curs)
	{
		g_linei->content[g_linei->curs] = c;
		ft_putchar(c);
	}
	else
	{
		ft_memmove(&g_linei->content[g_linei->curs + 1], &g_linei->content[g_linei->curs], ft_strlen(&g_linei->content[g_linei->curs]));
		g_linei->content[g_linei->curs] = c;
		ft_putchar(c);
		tputs(tgetstr("sc", NULL), 1, &put_my_char);
		ft_putstr(&g_linei->content[g_linei->curs + 1]);
		tputs(tgetstr("rc", NULL), 1, &put_my_char);
	}
	if (g_linei->curs != g_linei->len && g_linei->pos == ws.ws_col)
	{
		tputs(tgetstr("up", NULL), 1, &put_my_char);
		g_linei->pos = 0;
	}
	if (g_linei->col + 1 == ws.ws_col)
	{
		tputs(tgetstr("do", NULL), 1, &put_my_char);
		g_linei->col = 0;
	}
	g_linei->curs += 1;
	g_linei->col += 1;
	g_linei->len += 1;
	g_linei->pos += 1;
}

int	key_is_arrow_right(const char *buff)
{
	static char		enter_key[] = {91, 67, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_arrow_top(const char *buff)
{
	static char	enter_key[] = {91, 65, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_arrow_down(const char *buff)
{
	static char	enter_key[] = {91, 66, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_arrow_left(const char *buff)
{
	static char	enter_key[] = {91, 68, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

/*int	key_is_enter(const char *buff)
{
	static char	enter_key[] = {10, 0, 0, 0, 0, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}*/

void	key_left_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	tputs(tgetstr("le", NULL), 1, &put_my_char);
	if (g_linei->curs)
	{
		if (g_linei->col == 0)
			g_linei->col = ws.ws_col + 1;
		g_linei->curs -= 1;
		g_linei->col -= 1;
	}
}

void	key_right_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->col + 1 == ws.ws_col)
	{
		tputs(tgetstr("do", NULL), 1, &put_my_char);
		g_linei->curs += 1;
		g_linei->col = 0;
	}
	else if (g_linei->curs < ft_strlen(g_linei->content))
	{
		tputs(tgetstr("nd", NULL), 1, &put_my_char);
		g_linei->curs += 1;
		g_linei->col += 1;
	}
}

/*void	key_backspace_funct(void)
{
	key_left_funct();
	tputs(tgetstr("dc", NULL), 1, &put_my_char);
	ft_memmove(&g_line_info->line[g_line_info->curs],
			&g_line_info->line[g_line_info->curs + 1],
			ft_strlen(&g_line_info->line[g_line_info->curs]));
}

void	is_key(char *buff)
{
	//TODO
}*/

void	is_arrow(void)
{
	char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 5);
	if (key_is_arrow_left(buff))
		key_left_funct();
	if (key_is_arrow_right(buff))
		key_right_funct();
}

int main(void)
{
	char			buff[1];
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	init_term();
	g_linei = (struct s_linfo*)ft_memalloc(sizeof(struct s_linfo));
	g_linei->content = ft_strnew(20);
	g_linei->len = 0;
	g_linei->pos = 0;
	g_linei->curs = 0;
	g_linei->col = 0;
	g_linei->max_len = 20;
	while (1)
	{
		ft_bzero(buff, 1);
		read(0, buff, 1);
		// Faire un tableau de pointeur sur fonction
		if (buff[0] == 27)
			is_arrow();
		else if (ft_isprint(buff[0]))
			add_char_to_line(buff[0]);
		/*else if (key_is_arrow_left(buff))
			key_left_funct();
		else if (key_is_arrow_right(buff))
			key_right_funct();
		else if (buff[0] == 127)
			key_backspace_funct();*/
		else if (buff[0] == 10)
		{
			printf("\nLine = [%s]\n", g_linei->content);
			printf("Cursor = [%d]\n", g_linei->curs);
			printf("Len = [%d]\n", g_linei->len);
			printf("Pos = [%d]\n", g_linei->pos);
			printf("Winsize = [%d]\n", ws.ws_col);
			//printf("col = %d et line = %d", getColumnPosition(0, 1), getLinePosition(0, 1));
			exit(0);
		}
	}
	default_term();
}
