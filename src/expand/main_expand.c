/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 09:37:02 by lbopp             #+#    #+#             */
/*   Updated: 2017/06/08 14:15:04 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lsh.h"

char	*get_var_content(char *var_env)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		if (ft_strnequ(g_env[i], var_env,
					ft_strchr(g_env[i], '=') - g_env[i]) &&
				(long)ft_strlen(var_env) == ft_strchr(g_env[i], '=')
				- g_env[i])
		{
			free(var_env);
			return (ft_strchr(g_env[i], '=') + 1);
		}
		i += 1;
	}
	free(var_env);
	return (NULL);
}

int		get_last_st(t_state *st_lst)
{
	int		last_state;
	t_state	*previous;

	previous = NULL;
	while (st_lst)
	{
		previous = st_lst;
		st_lst = st_lst->next;
	}
	last_state = 0;
	if (previous)
		last_state = previous->state;
	return (last_state);
}

void	put_in_env_array(char ***array_env, char **content, int *i)
{
	char	**new_array;
	int		curs;

	curs = 0;
	if (!*array_env)
		*array_env = (char**)ft_memalloc(sizeof(char*) * 10);
	else if (*i % 10 == 0)
	{
		new_array = (char**)ft_memalloc(sizeof(char*) * *i + 10);
		while (curs < *i)
		{
			new_array[curs] = ft_strdup((*array_env)[curs]);
			curs += 1;
		}
		ft_memmove(*array_env, new_array, sizeof(new_array));
	}
	if (*content)
		(*array_env)[*i] = ft_strdup(*content);
	else
		(*array_env)[*i] = NULL;
	*i += 1;
}

char	*expand_add_char(char *content, int i, int size_var, t_state *st_lst)
{
	char	*var_env;

	var_env = NULL;
	if (!st_lst)
		var_env = get_var_content(
				ft_strsub((char const*)content, i, size_var));
	else if (get_last_st(st_lst) == DQUOTE)
	{
		var_env = ft_strdup("\"");
		var_env = ft_stradd(var_env, get_var_content(
					ft_strsub((char const*)content, i, size_var)));
		var_env = ft_stradd(var_env, "\"");
	}
	else
	{
		var_env = ft_strdup("$");
		var_env = ft_stradd(var_env,
				ft_strsub((char const*)content, i, size_var));
	}
	return (var_env);
}

void	expand_var_env(char **content, char ***array_env, int *curs)
{
	t_state	*st_lst;
	int		i;
	int		size_var;
	char	*var_env;

	i = 0;
	st_lst = NULL;
	while (*content && (*content)[i])
	{
		size_var = 0;
		if ((*content)[i] == '\'' || (*content)[i] == '"')
			state_management(&st_lst, (*content)[i]);
		if ((*content)[i] == '$')
		{
			i += 1;
			while ((*content)[i + size_var] &&
				(ft_isalnum((*content)[i + size_var]) ||
					 (*content)[i + size_var] == '_'))
				size_var += 1;
			var_env = expand_add_char(*content, i, size_var, st_lst);
			put_in_env_array(array_env, &var_env, curs);
			i += size_var;
		}
		i = size_var ? i : i + 1;
	}
}

void	replace_content(char **before, char **new, char **after, char **content)
{
	if (*new || *before || *after)
	{
		ft_strdel(content);
		*content = ft_strnew(0);
		if (*before)
		{
			*content = ft_stradd(*content, *before);
			ft_strdel(before);
		}
		if (*new)
		{
			*content = ft_stradd(*content, *new);
			ft_strdel(new);
		}
		if (*after)
		{
			*content = ft_stradd(*content, *after);
			ft_strdel(after);
		}
	}
}

char	*expand_quote_remove(char **content)
{
	int		i;
	char	tmp;
	char	*before;
	char	*new;
	char	*after;

	i = 0;
	before = NULL;
	while ((*content)[i])
	{
		if ((*content)[i] == '\'' || (*content)[i] == '"')
		{
			before = ft_strsub(*content, 0, i);
			tmp = (*content)[i];
			i += 1;
			while (tmp != (*content)[i])
				i += 1;
			new = ft_strsub(*content,
					ft_strlen(before) + 1, i - 1 - ft_strlen(before));
			after = ft_strsub(*content, i + 1, ft_strlen(*content) - i + 1);
			after = expand_quote_remove(&after);
			replace_content(&before, &new, &after, content);
		}
		i += 1;
	}
	return (*content);
}

char	*expand_replace_var(char **content, char **array_env, int i_env)
{
	int		i;
	char	*before;
	char	*new;
	char	*after;

	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$')
		{
			before = ft_strsub(*content, 0, i);
			i += 1;
			while ((ft_isalnum((*content)[i]) || (*content)[i] == '_'))
				i += 1;
			new = array_env[i_env];
			after = ft_strsub(*content, i, ft_strlen(*content) - i);
			after = expand_replace_var(&after, array_env, i_env + 1);
			replace_content(&before, &new, &after, content);
		}
		i += 1;
	}
	return (*content);
}

void	remove_quote_array_env(char ***array_env, int max)
{
	int		i;
	char	*new;

	i = 0;
	while (i < max)
	{
		if ((*array_env)[i] && (*array_env)[i][0] && ((*array_env[i])[0] == '"' ||
					(*array_env[i])[0] == '\''))
		{
			new = ft_strsub((*array_env)[i], 1, ft_strlen((*array_env[i])) - 2);
			free((*array_env[i]));
			(*array_env)[i] = new;
		}
		i += 1;
	}
}

void	launch_expand(t_list **list)
{
	static char	**array_env = NULL;
	static int	curs = 0;
	t_list		*origin;
	int			i;

	origin = *list;
	while (origin)
	{
		i = 0;
		expand_var_env((char**)&origin->content, &array_env, &curs);
		origin->content =
			expand_quote_remove((char**)&origin->content);
		while (i < curs)
			i += 1;
		remove_quote_array_env(&array_env, curs);
		i = 0;
		while (i < curs)
			i += 1;
		origin->content =
			expand_replace_var((char**)&origin->content, array_env, 0);
		curs = 0;
		array_env = NULL;
		origin = origin->next;
	}
}

void	main_expand(t_ast_node **ast_tree)
{
	if (!*ast_tree)
		return ;
	if ((*ast_tree)->left)
		main_expand(&(*ast_tree)->left);
	if ((*ast_tree)->right)
		main_expand(&(*ast_tree)->right);
	launch_expand(&(*ast_tree)->content);
}
