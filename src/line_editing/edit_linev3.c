/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_linev3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:58:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/27 16:02:56 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"
#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

struct termios		g_origin_term;
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
	int		len;
	int		len_max;
}				t_lineinfo;
t_lineinfo	*g_linei;
void	default_term(void);
void	save_reset_pos(t_pos pos, int mode);

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

int	key_is_arrow_right(const char *buff)
{
	static char		enter_key[] = {91, 67, 0, 0, 0};

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

int	key_is_home(const char *buff)
{
	static char	enter_key[] = {91, 72, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_end(const char *buff)
{
	static char	enter_key[] = {91, 70, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_shift_left(const char *buff)
{
	static char	enter_key[] = {91, 49, 59, 50, 68, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_shift_up(const char *buff)
{
	static char	enter_key[] = {91, 49, 59, 50, 65, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_shift_down(const char *buff)
{
	static char	enter_key[] = {91, 49, 59, 50, 66, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_shift_right(const char *buff)
{
	static char	enter_key[] = {91, 49, 59, 50, 67, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

void	key_left_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != 0)
	{
		if (g_linei->pos.x == 0 && g_linei->pos.y != 0) 
		{
			tputs(tgetstr("up", NULL), 1, &put_my_char);
			g_linei->pos.y -= 1;
			while (g_linei->pos.x != ws.ws_col)
			{
				tputs(tgetstr("nd", NULL), 1, &put_my_char);
				g_linei->pos.x += 1;
			}
		}
		else
			tputs(tgetstr("le", NULL), 1, &put_my_char);
		g_linei->pos.x -= 1;
		g_linei->curs -= 1;
	}
}

void	key_right_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != g_linei->len)
	{
		if (g_linei->pos.x + 1 == ws.ws_col)
		{
			tputs(tgetstr("do", NULL), 1, &put_my_char);
			g_linei->pos.x = 0;
			g_linei->pos.y += 1;
		}
		else
		{
			tputs(tgetstr("nd", NULL), 1, &put_my_char);
			g_linei->pos.x += 1;
		}
		g_linei->curs += 1;
	}
}

void	key_home_funct(void)
{
	t_pos	tmp_pos;

	tmp_pos.x = 0;
	tmp_pos.y = 0;
	save_reset_pos(tmp_pos, 1);
	save_reset_pos(g_linei->pos, 2);
}

void	key_end_funct(void)
{
	t_pos			tmp_pos;
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	tmp_pos.x = g_linei->len % ws.ws_col;
	tmp_pos.y = g_linei->len / ws.ws_col;
	save_reset_pos(tmp_pos, 1);
	save_reset_pos(g_linei->pos, 2);
}

void	key_shift_left_funct()
{
	int	sp;

	sp = 0;
	key_left_funct();
	while (g_linei->curs && g_linei->content[g_linei->curs] == ' ')
	{
		key_left_funct();
		sp = 1;
	}
	while (g_linei->curs && ft_isalnum(g_linei->content[g_linei->curs]))
		key_left_funct();
	if (g_linei->curs)
		key_right_funct();
}

void	key_shift_right_funct()
{
	int	sp;

	sp = 0;
	key_right_funct();
	while (g_linei->curs && ft_isalnum(g_linei->content[g_linei->curs]) && !sp)
		key_right_funct();
	while (g_linei->curs && g_linei->content[g_linei->curs] == ' ')
	{
		key_right_funct();
		sp = 1;
	}
}

void	key_shift_up_funct()
{
	t_pos	tmp_pos;

	if (g_linei->pos.y - 1 >= 0)
	{
		tmp_pos.x = g_linei->pos.x;
		tmp_pos.y = g_linei->pos.y - 1;
		save_reset_pos(tmp_pos, 1);
		save_reset_pos(g_linei->pos, 2);
	}
}

void	key_shift_down_funct()
{
	t_pos	tmp_pos;
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->pos.y + 1 <= g_linei->len / ws.ws_col)
	{
		if (g_linei->pos.x * (g_linei->pos.y + 1) + ws.ws_col <= g_linei->len)
			tmp_pos.x = g_linei->pos.x;
		else
			tmp_pos.x = g_linei->len - (g_linei->pos.y + 1) * ws.ws_col;
		tmp_pos.y = g_linei->pos.y + 1;
		save_reset_pos(tmp_pos, 1);
		save_reset_pos(g_linei->pos, 2);
	}
}

void	is_arrow(void)
{
	char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 5);
	if (key_is_arrow_left(buff))
		key_left_funct();
	if (key_is_arrow_right(buff))
		key_right_funct();
	if (key_is_home(buff))
		key_home_funct();
	if (key_is_end(buff))
		key_end_funct();
	if (key_is_shift_left(buff))
		key_shift_left_funct();
	if (key_is_shift_right(buff))
		key_shift_right_funct();
	if (key_is_shift_up(buff))
		key_shift_up_funct();
	if (key_is_shift_down(buff))
		key_shift_down_funct();
}

void	save_reset_pos(t_pos pos, int mode)
{
	static t_pos	tmp_pos = {0, 0};
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (mode == 1)
		tmp_pos = pos;
	else
	{
		while (g_linei->pos.y > tmp_pos.y)
		{
			g_linei->pos.y -= 1;
			g_linei->curs -= ws.ws_col;
			tputs(tgetstr("up", NULL), 1, &put_my_char);
		}
		while (g_linei->pos.y < tmp_pos.y)
		{
			g_linei->pos.y += 1;
			g_linei->curs -= g_linei->pos.x;
			g_linei->pos.x = 0;
			g_linei->curs += ws.ws_col;
			tputs(tgetstr("do", NULL), 1, &put_my_char);
		}
		while (g_linei->pos.x > tmp_pos.x)
		{
			g_linei->pos.x -= 1;
			g_linei->curs -= 1;
			tputs(tgetstr("le", NULL), 1, &put_my_char);
		}
		while (g_linei->pos.x < tmp_pos.x)
		{
			g_linei->pos.x += 1;
			g_linei->curs += 1;
			tputs(tgetstr("nd", NULL), 1, &put_my_char);
		}
	}
}

void	put_my_str_edit(char *content)
{
	int	i;
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	i = 0;
	while (content[i])
	{
		ft_putchar(content[i]);
		g_linei->pos.x += 1;
		g_linei->curs += 1;
		if (g_linei->pos.x == ws.ws_col)
		{
			g_linei->pos.x = 0;
			tputs(tgetstr("do", NULL), 1, &put_my_char);
			g_linei->pos.y += 1;
		}
		i += 1;
	}
}

char	*realloc_char(char **ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = NULL;
	new_ptr = (char*)ft_memalloc(sizeof(char) * size);
	if (*ptr && new_ptr)
		ft_memmove(new_ptr, *ptr, ft_strlen(*ptr));
	//ft_strdel(ptr);
	return (new_ptr);
}

void	add_char_enter_char(char c)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	ft_memmove(&g_linei->content[g_linei->curs + 1],
			&g_linei->content[g_linei->curs],
			ft_strlen(&g_linei->content[g_linei->curs]));
	g_linei->content[g_linei->curs] = c;
	ft_putchar(c);
	g_linei->curs += 1;
	g_linei->pos.x += 1;
	if (g_linei->pos.x == ws.ws_col)
	{
		g_linei->pos.x = 0;
		tputs(tgetstr("do", NULL), 1, &put_my_char);
		g_linei->pos.y += 1;
	}
	save_reset_pos(g_linei->pos, 1);
	put_my_str_edit(&g_linei->content[g_linei->curs]);
	save_reset_pos(g_linei->pos, 2);
	g_linei->len += 1;
}

void	add_char_at_end(char c)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->len == g_linei->len_max)
	{
		g_linei->content =
			realloc_char(&g_linei->content, g_linei->len_max + 21);
		ft_bzero(&g_linei->content[g_linei->len_max], 21);
		g_linei->len_max += 20;
	}
	g_linei->content[g_linei->curs] = c;
	ft_putchar(c);
	g_linei->curs += 1;
	g_linei->pos.x += 1;
	g_linei->len += 1;
	if (g_linei->pos.x == ws.ws_col)
	{
		tputs(tgetstr("do", NULL), 1, &put_my_char);
		g_linei->pos.y += 1;
		g_linei->pos.x = 0;
	}
}

void	add_char_to_line(char c)
{
	if (g_linei->len == g_linei->len_max)
	{
		g_linei->content =
			realloc_char(&g_linei->content, g_linei->len_max + 21);
		ft_bzero(&g_linei->content[g_linei->len_max], 21);
		g_linei->len_max += 20;
	}
	if (g_linei->curs == g_linei->len)
		add_char_at_end(c);
	else
		add_char_enter_char(c);
}

void	del_char(void)
{
	if (g_linei->len)
	{
		key_left_funct();
		tputs(tgetstr("dc", NULL), 1, &put_my_char);
		ft_memmove(&g_linei->content[g_linei->curs], &g_linei->content[g_linei->curs + 1],
				ft_strlen(&g_linei->content[g_linei->curs + 1]));
		g_linei->content[ft_strlen(g_linei->content) - 1] = '\0';
		g_linei->len -= 1;
	}
}

int	main(void)
{
	char		buf[1];
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	init_term();
	g_linei = ft_memalloc(sizeof(t_lineinfo));
	g_linei->content = ft_strnew(20);
	g_linei->len = 0;
	g_linei->len_max = 20;
	g_linei->pos.x = 0;
	g_linei->pos.y = 0;
	g_linei->curs = 0;
	while (1)
	{
		ft_bzero(buf, 1);
		read(0, buf, 1);
		if (buf[0] == 27)
			is_arrow();
		else if (buf[0] == 127) // Backspace
			del_char();
		else if (ft_isprint(buf[0]))
			add_char_to_line(buf[0]);
		else if (buf[0] == 10)
		{
			printf("\nCURS = [%d]\n", g_linei->curs);
			printf("LINE = [%s]\n", g_linei->content);
			printf("LEN = [%d]\n", g_linei->len);
			printf("COL = [%d]\n", g_linei->pos.x);
			printf("SIZE = [%d]\n", ws.ws_col);
			g_linei->curs = 0;
			exit(0);
		}
	}
	default_term();
}
