#include "lsh.h"
#include <stdio.h>
#include <term.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

struct termios		g_origin_term;
void	default_term(void);
typedef struct	s_lineinfo
{
	int		col;	//position du curseur sur la ligne
	char	*content;
	int		curs;
	int		pos;	//position de la fin du contenu sur la ligne;
	int		row;	//nombre de ligne que prend le contenu
	int		len;
	int		len_max;
}				t_lineinfo;
t_lineinfo	*g_linei;

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

void	key_left_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != 0)
	{
		if (g_linei->col == 0)
		{
			tputs(tgetstr("up", NULL), 1, &put_my_char);
			while (g_linei->col != ws.ws_col)
			{
				g_linei->col += 1;
				tputs(tgetstr("nd", NULL), 1, &put_my_char);
			}
		}
		else
		{
			tputs(tgetstr("le", NULL), 1, &put_my_char);
			g_linei->col -= 1;
		}
		g_linei->curs -= 1;
	}
}

void	key_right_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != g_linei->len)
	{
		if (g_linei->col == ws.ws_col)
		{
			tputs(tgetstr("do", NULL), 1, &put_my_char);
			g_linei->col = 0;
			g_linei->row += 1;
		}
		else
		{
			tputs(tgetstr("nd", NULL), 1, &put_my_char);
			g_linei->col += 1;
		}
		g_linei->curs += 1;
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
}

void	put_str_edit(char *content)
{
	struct winsize	ws;
	int				i;

	ioctl(1, TIOCGWINSZ, &ws);
	if ((size_t)ws.ws_col - g_linei->col > ft_strlen(content))
		ft_putstr(content);
	else
	{
		i = 0;
		while (content[i])
		{
			while (g_linei->col < ws.ws_col && content[i])
			{
				ft_putchar(content[i]);
				g_linei->col += 1;
				i += 1;
			}
			if (content[i])
					g_linei->col = 0;
			tputs(tgetstr("do", NULL), 1, &put_my_char);
			g_linei->row += 1;
		}
	}
}

void	add_char_to_line(char c)
{
	struct winsize	ws;
	int tmp;

	ioctl(1, TIOCGWINSZ, &ws);
	//TODO Si plus de 20 char faut rallouer
	if (g_linei->curs == g_linei->len) //Si on est au bout de la ligne
	{
		g_linei->content[g_linei->curs] = c;
		ft_putchar(c);
		g_linei->curs += 1;
		g_linei->col += 1;
		g_linei->len += 1;
		if (g_linei->col == ws.ws_col)
		{
			tputs(tgetstr("do", NULL), 1, &put_my_char);
			g_linei->row += 1;
			g_linei->col = 0;
		}
	}
	else
	{
		ft_memmove(&g_linei->content[g_linei->curs + 1],
				&g_linei->content[g_linei->curs], ft_strlen(&g_linei->content[g_linei->curs]));
		g_linei->content[g_linei->curs] = c;
		ft_putchar(c);
		put_str_edit(&g_linei->content[g_linei->curs + 1]);
		tmp = g_linei->curs + 1;
		g_linei->curs = g_linei->len + 1;
		while (g_linei->curs != tmp)
		{
			g_linei->curs -= 1;
			tputs(tgetstr("le", NULL), 1, &put_my_char);
		}
		g_linei->col += 1;
		g_linei->len += 1;
	}
}

int	main()
{
	char		buf[1];
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);

	init_term();
	g_linei = ft_memalloc(sizeof(t_lineinfo));
	g_linei->content = ft_strnew(20);
	g_linei->len = 0;
	g_linei->len_max = 20;
	g_linei->row = 0;
	while (1)
	{
		ft_bzero(buf, 1);
		read(0, buf, 1);
		if (buf[0] == 27)
			is_arrow();
		else if (ft_isprint(buf[0]))
			add_char_to_line(buf[0]);
		else if (buf[0] == 10)
		{
			printf("\nCURS = [%d]\n", g_linei->curs);
			printf("LINE = [%s]\n", g_linei->content);
			printf("LEN = [%d]\n", g_linei->len);
			printf("COL = [%d]\n", g_linei->col);
			printf("SIZE = [%d]\n", ws.ws_col);
			g_linei->curs = 0;
		}
	}
	default_term();
}
