#include "lsh.h"

void	save_history(void)
{
	int	fd;

	fd = open(".lsh_history", O_RDWR | O_CREAT, 0644);
	while (g_history->prev)
		g_history = g_history->prev;
	while (g_history)
	{
		ft_putendl_fd(g_history->content, fd);
		g_history = g_history->next;
	}
	//Need to free this list;
	close(fd);
}

void	merge_history(t_list_double **prev, t_list_double **merge)
{
	(*prev)->content = ft_stradd((*prev)->content, "\n");
	(*prev)->content = ft_stradd((*prev)->content, (*merge)->content);
	ft_strdel(&(*merge)->content);
	(*prev)->next = NULL;
	//free(*merge);
}

void	add_to_history(char	*line)
{
	static t_list_double	*last;

	if (!g_history)
	{
		g_history = (t_list_double*)ft_memalloc(sizeof(t_list_double));
		g_history->content = ft_strdup(line);
		g_history->next = NULL;
		g_history->prev = NULL;
		last = g_history;
	}
	else
	{
		last = g_history;
		g_history->next = (t_list_double*)ft_memalloc(sizeof(t_list_double));
		g_history->next->content = ft_strdup(line);
		g_history->next->prev = last;
		g_history->next->next = NULL;
		g_history = g_history->next;
	}
}

void	main_history(void)
{
	int		fd;
	char	*line;

	fd = open(".lsh_history", O_RDWR | O_CREAT, 0644);
	line = NULL;
	g_history = NULL;
	while (get_next_line(fd, &line) && line)
	{
		add_to_history(line);
		ft_strdel(&line);
	}
	close(fd);
}
