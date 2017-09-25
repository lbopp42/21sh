/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_linev3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:58:28 by lbopp             #+#    #+#             */
/*   Updated: 2017/09/25 11:41:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

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

int	key_is_arrow_up(const char *buff)
{
	static char	up_key[] = {91, 65, 0, 0, 0};

	if (!ft_strcmp(buff, up_key))
		return (1);
	return (0);
}

int	key_is_arrow_down(const char *buff)
{
	static char	down_key[] = {91, 66, 0, 0, 0};

	if (!ft_strcmp(buff, down_key))
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

int	key_is_alt_right(const char *buff)
{
	static char	enter_key[] = {27, 91, 67, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_alt_left(const char *buff)
{
	static char	enter_key[] = {27, 91, 68, 0, 0, 0};

	if (!ft_strcmp(buff, enter_key))
		return (1);
	return (0);
}

int	key_is_alt_v(const char *buff)
{
	static char	alt_v[] = {-120, -102, 0, 0, 0, 0};
	char		buff2[6];

	if (buff[0] == -30)
	{
		ft_bzero(buff2, 6);
		read(0, buff2, 5);
		if (buff2[0] == alt_v[0] && buff2[1] == alt_v[1] &&
				!buff2[2])
			return (1);
	}
	return (0);
}

int		key_is_alt_c(char *buff)
{
	static char	alt_c_key[] = {-61, -89, 0, 0, 0, 0};

	if (!ft_strcmp(buff, alt_c_key))
		return (1);
	return (0);
}

int		key_is_alt_p(char *buff)
{
	static char	alt_p_key[] = {-128, 0, 0, 0, 0};
	char		buff2[5];

	if (buff[0] == -49)
	{
		ft_bzero(buff2, 5);
		read(0, buff2, 5);
		if (!ft_strcmp(buff2, alt_p_key))
			return (1);
	}
	return (0);
}

int		key_is_alt_x(char *buff)
{
	static char	alt_x[] = {-30, -119, -120, 0, 0, 0};

	if (buff[0] == alt_x[0] && buff[1] == alt_x[1] &&
			buff[2] == alt_x[2] && !buff[3])
		return (1);
	return (0);
}

void	key_home_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	while (g_linei->pos.y)
	{
		tputs(tgetstr("up", NULL), 1, &put_my_char);
		g_linei->pos.y--;
	}
	while (g_linei->pos.x > g_linei->p_len)
	{
		tputs(tgetstr("le", NULL), 1, &put_my_char);
		g_linei->pos.x--;
	}
	while (g_linei->pos.x < g_linei->p_len)
	{
		tputs(tgetstr("nd", NULL), 1, &put_my_char);
		g_linei->pos.x++;
	}
	g_linei->curs = 0;
}
/*
**	Peut etre une erreur ici pos.x = 0 serai = p_len pour y = 0
*/
void	key_right_funct(void)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != g_linei->len)
	{
		if (g_linei->pos.x + 1 == ws.ws_col ||
				g_linei->content[g_linei->curs] == '\n')
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

void	key_left_funct(void)
{
	struct winsize	ws;
	int				tmp_curs;

	ioctl(1, TIOCGWINSZ, &ws);
	if (g_linei->curs != 0)
	{
		if (g_linei->pos.x == 0 && g_linei->pos.y != 0 &&
				g_linei->content[g_linei->curs - 1] == '\n')
		{
			tmp_curs = g_linei->curs;
			key_home_funct();
			while (g_linei->curs < tmp_curs - 1)
				key_right_funct();
			g_linei->curs++;
			g_linei->pos.x++;
		}
		else if (g_linei->pos.x == 0 && g_linei->pos.y != 0)
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

void	key_up_funct(char **first_select)
{
	if (g_history->prev)
	{
		if (!(*first_select))
			*first_select = ft_strdup(g_linei->content);
		else
			g_history = g_history->prev;
		key_home_funct();
		tputs(tgetstr("cd", NULL), 1, &put_my_char);
		ft_strdel(&g_linei->content);
		g_linei->content = ft_strdup(g_history->content);
		g_linei->len = ft_strlen(g_history->content);
		g_linei->len_max = g_linei->len;
		put_my_str_edit(g_linei->content);
	}
}

void	key_down_funct(char **first_select)
{
	if (g_history->next)
	{
		g_history = g_history->next;
		key_home_funct();
		tputs(tgetstr("cd", NULL), 1, &put_my_char);
		ft_strdel(&g_linei->content);
		g_linei->content = ft_strdup(g_history->content);
		g_linei->len = ft_strlen(g_history->content);
		g_linei->len_max = g_linei->len;
		put_my_str_edit(g_linei->content);
	}
	else if (*first_select)
	{
		key_home_funct();
		tputs(tgetstr("cd", NULL), 1, &put_my_char);
		ft_strdel(&g_linei->content);
		g_linei->content = ft_strdup(*first_select);
		g_linei->len = ft_strlen(*first_select);
		g_linei->len_max = g_linei->len;
		put_my_str_edit(g_linei->content);
		ft_strdel(first_select);
	}
}

void	key_end_funct(void)
{
	while (g_linei->len > g_linei->curs)
		key_right_funct();
}

void	key_shift_left_funct(void)
{
	int	sp;

	sp = 0;
	key_left_funct();
	while (g_linei->curs && (g_linei->content[g_linei->curs] == ' ' ||
			g_linei->content[g_linei->curs] == '\n'))
		key_left_funct();
		sp = 1;
	while (g_linei->curs && ft_isprint(g_linei->content[g_linei->curs])
			&& !ft_isspace(g_linei->content[g_linei->curs]))
		key_left_funct();
	if (g_linei->curs)
		key_right_funct();
}

void	key_shift_right_funct(void)
{
	int	sp;

	sp = 0;
	key_right_funct();
	while (g_linei->curs < g_linei->len &&
			ft_isprint(g_linei->content[g_linei->curs]) && !sp
			&& !ft_isspace(g_linei->content[g_linei->curs]))
		key_right_funct();
	while (g_linei->curs < g_linei->len &&
			(g_linei->content[g_linei->curs] == ' ' ||
			g_linei->content[g_linei->curs] == '\n'))
	{
		key_right_funct();
		sp = 1;
	}
}

void	key_shift_up_funct(void)
{
	t_pos	tmp_pos;

	if (g_linei->pos.y - 1 >= 0)
	{
		tmp_pos.x = g_linei->pos.x;
		tmp_pos.y = g_linei->pos.y - 1;
		key_home_funct();
		while (g_linei->pos.y < tmp_pos.y)
			key_right_funct();
		while (g_linei->pos.x < tmp_pos.x &&
				g_linei->content[g_linei->curs] != '\n')
			key_right_funct();
	}
}

void	key_shift_down_funct(void)
{
	t_pos			tmp_pos;

	tmp_pos.x = g_linei->pos.x;
	tmp_pos.y = g_linei->pos.y + 1;
	while (g_linei->pos.y < tmp_pos.y &&
			g_linei->curs < g_linei->len)
		key_right_funct();
	while (g_linei->pos.x < tmp_pos.x &&
			g_linei->content[g_linei->curs] != '\n')
		key_right_funct();
}

void	is_arrow(char **first_select)
{
	char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 5);
	if (key_is_arrow_left(buff))
		key_left_funct();
	if (key_is_arrow_right(buff))
		key_right_funct();
	if (key_is_arrow_up(buff))
		key_up_funct(first_select);
	if (key_is_arrow_down(buff))
		key_down_funct(first_select);
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

void	move_to_x(t_pos tmp_pos)
{
	while (g_linei->pos.x > tmp_pos.x)
		key_left_funct();
	while (g_linei->pos.x < tmp_pos.x)
		key_right_funct();
}

void	move_to_y(t_pos tmp_pos, struct winsize ws)
{
	(void)ws;
	while (g_linei->pos.y > tmp_pos.y)
		key_left_funct();
	while (g_linei->pos.y < tmp_pos.y)
		key_right_funct();
}

void	move_to(t_pos tmp_pos)
{
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	move_to_y(tmp_pos, ws);
	move_to_x(tmp_pos);
}

void	save_reset_pos(t_pos pos, int mode)
{
	static t_pos	tmp_pos = {0, 0};

	if (mode == 1)
		tmp_pos = pos;
	else
		move_to(tmp_pos);
}

void	put_my_str_edit(char *content)
{
	int				i;
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	i = 0;
	while (content[i])
	{
		ft_putchar(content[i]);
		g_linei->pos.x += 1;
		if (content[i] == '\n')
		{
			g_linei->pos.x = 0;
			g_linei->pos.y += 1;
		}
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

char	*cut_funct(char *selected)
{
	char	*cutted;
	char	*new_line;

	cutted = ft_strdup(selected);
	move_to(g_linei->select_start);
	tputs(tgetstr("cd", NULL), 1, &put_my_char);
	save_reset_pos(g_linei->pos, 1);
	put_my_str_edit(&g_linei->content[g_linei->curs + ft_strlen(cutted)]);
	save_reset_pos(g_linei->pos, 2);
	g_linei->len -= ft_strlen(cutted);
	new_line = ft_strsub(g_linei->content, 0, g_linei->curs);
	new_line = ft_stradd(new_line,
			&g_linei->content[g_linei->curs + ft_strlen(cutted)]);
	free(g_linei->content);
	g_linei->content = new_line;
	return (cutted);
}

void	remove_select_to_right(int *i, char **selected)
{
	char		*tmp_select;
	char		tmp[2];

	tmp[1] = '\0';
	tmp[0] = g_linei->content[g_linei->curs];
	save_reset_pos(g_linei->pos, 1);
	tmp_select = ft_strdup(*selected + 1);
	free(*selected);
	*selected = ft_strdup(tmp_select);
	free(tmp_select);
	put_my_str_edit(tmp);
	save_reset_pos(g_linei->pos, 2);
	key_right_funct();
	g_linei->select_start = g_linei->pos;
	(*i)++;
}

void	select_to_right(int *i, char **selected)
{
	char		tmp[2];

	tmp[1] = '\0';
	if (*i > 0 && g_linei->curs < g_linei->len)
	{
		key_right_funct();
		save_reset_pos(g_linei->pos, 1);
		tmp[0] = g_linei->content[g_linei->curs];
		*selected = ft_stradd(*selected, tmp);
		ft_putstr("\033[7m"); // NE PAS ECRIRE SUR 1 (probleme du ls)
		put_my_str_edit(&(*selected)[(*i)++]);
		save_reset_pos(g_linei->pos, 2);
		ft_putstr("\033[0m"); // NE PAS ECRIRE SUR 1
	}
	else if (g_linei->curs < g_linei->len)
		remove_select_to_right(i, selected);
}

void	remove_select_to_left(int *i, char **selected)
{
	char		*tmp_select;
	char		tmp[2];

	tmp[1] = '\0';
	tmp_select = ft_strdup(*selected);
	ft_strdel(selected);
	key_left_funct();
	g_linei->select_start = g_linei->pos;
	tmp[0] = g_linei->content[g_linei->curs];
	*selected = ft_strdup(tmp);
	*selected = ft_stradd(*selected, tmp_select);
	free(tmp_select);
	save_reset_pos(g_linei->pos, 1);
	ft_putstr("\033[7m"); // NE PAS ECRIRE SUR 1
	put_my_str_edit(*selected);
	save_reset_pos(g_linei->pos, 2);
	ft_putstr("\033[0m"); // NE PAS ECRIRE SUR 1
	(*i)--;
}

void	select_to_left(int *i, char **selected)
{
	char		tmp[2];

	tmp[1] = '\0';
	if (*i - 1 > 0)
	{
		tmp[0] = g_linei->content[g_linei->curs];
		put_my_str_edit(tmp);
		save_reset_pos(g_linei->pos, 2);
		(*selected)[*i - 1] = '\0';
		(*i)--;
		key_left_funct();
		save_reset_pos(g_linei->pos, 1);
	}
	else
		remove_select_to_left(i, selected);
}

void	treat_key_select(int *i, char buff[], char **selected, char **copy)
{
	while (buff[0] == 27 && (key_is_arrow_right(buff + 1) ||
				key_is_arrow_left(buff + 1)))
	{
		if (key_is_arrow_right(buff + 1))
			select_to_right(i, selected);
		else if (key_is_arrow_left(buff + 1) && g_linei->curs > 0)
			select_to_left(i, selected);
		ft_bzero(buff, 6);
		read(0, buff, 5);
	}
	if (key_is_alt_c(buff))
		*copy = ft_strdup(*selected);
	else if (key_is_alt_x(buff))
	{
		*copy = cut_funct(*selected);
		return ;
	}
	save_reset_pos(g_linei->pos, 1);
	move_to(g_linei->select_start);
	put_my_str_edit(&(*selected)[0]);
	save_reset_pos(g_linei->pos, 2);
}

char	*line_editing_select(int mode)
{
	char		*selected;
	static char	*copy = NULL;
	char		buff[6];
	int			i;

	if (mode == 1)
	{
		i = 1;
		g_linei->select_start = g_linei->pos;
		selected = ft_strnew(1);
		selected[0] = g_linei->content[g_linei->curs];
		save_reset_pos(g_linei->pos, 1);
		ft_putstr("\033[7m"); // NE PAS ECRIRE SUR 1
		put_my_str_edit(selected);
		save_reset_pos(g_linei->pos, 2);
		ft_putstr("\033[0m"); // NE PAS ECRIRE SUR 1
		ft_bzero(buff, 6);
		read(0, buff, 5);
		treat_key_select(&i, buff, &selected, &copy);
	}
	else if (mode == 2)
		return (copy);
	return (NULL);
}

char	*realloc_char(char **ptr, size_t size)
{
	char	*new_ptr;

	new_ptr = NULL;
	new_ptr = (char*)ft_memalloc(sizeof(char) * size);
	if (*ptr && new_ptr)
		ft_memmove(new_ptr, *ptr, ft_strlen(*ptr));
	ft_strdel(ptr);
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
	tputs(tgetstr("cd", NULL), 1, &put_my_char);
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
	if (g_linei->len && g_linei->curs)
	{
		key_left_funct();
		tputs(tgetstr("dc", NULL), 1, &put_my_char);
		ft_memmove(&g_linei->content[g_linei->curs],
				&g_linei->content[g_linei->curs + 1],
				ft_strlen(&g_linei->content[g_linei->curs + 1]));
		g_linei->content[ft_strlen(g_linei->content) - 1] = '\0';
		save_reset_pos(g_linei->pos, 1);
		tputs(tgetstr("cd", NULL), 1, &put_my_char);
		put_my_str_edit(&g_linei->content[g_linei->curs]);
		save_reset_pos(g_linei->pos, 2);
		g_linei->len -= 1;
	}
}

void	paste_select(void)
{
	char	*result;

	if (line_editing_select(2) == NULL)
		return ;
	result = ft_strsub(g_linei->content, 0, g_linei->curs);
	result = ft_stradd(result, line_editing_select(2));
	result = ft_stradd(result,
			ft_strsub(g_linei->content, g_linei->curs, g_linei->len - g_linei->curs));
	free(g_linei->content);
	g_linei->content = result;
	g_linei->len = ft_strlen(result);
	g_linei->len_max = g_linei->len;
	put_my_str_edit(line_editing_select(2));
	save_reset_pos(g_linei->pos, 1);
	put_my_str_edit(&g_linei->content[g_linei->curs]);
	save_reset_pos(g_linei->pos, 2);
}

void	init_line_info(int p_len)
{
	g_linei = ft_memalloc(sizeof(t_lineinfo));
	g_linei->content = ft_strnew(20);
	g_linei->p_len = p_len;
	g_linei->len = 0;
	g_linei->len_max = 20;
	g_linei->pos.x = g_linei->p_len;
	g_linei->pos.y = 0;
	g_linei->curs = 0;
}

int		treat_key(char buf[])
{
	static char*	first_select = NULL;

	if (buf[0] == 27)
		is_arrow(&first_select);
	else if (buf[0] == 127)// Backspace
		del_char();
	else if (key_is_alt_v(buf))
		line_editing_select(1);
	else if (ft_isprint(buf[0]))
		add_char_to_line(buf[0]);
	else if (key_is_alt_p(buf))
		paste_select();
	else if (buf[0] == 10)
	{
		key_end_funct();
		ft_strdel(&first_select);
		while (g_history && g_history->next)
			g_history = g_history->next;	
		g_linei->curs = 0;
		add_to_history(g_linei->content);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

char	*editing_line(int p_len)
{
	char			buf[1];
	static char		*exit[2] = {"exit", "0"};
	struct winsize	ws;

	ioctl(1, TIOCGWINSZ, &ws);
	init_line_info(p_len);
	init_term();
	while (1)
	{
		ft_bzero(buf, 1);
		read(0, buf, 1);
		if (buf[0] == 4)
		{
			save_history();
			default_term();
			ft_exit(exit);
		}
		else if (treat_key(buf))
		{
			default_term();
			return (g_linei->content);
		}
	}
	return (NULL);
}
