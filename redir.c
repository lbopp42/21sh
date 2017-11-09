#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char	*path;
	char	**split;
	int		i;
	char	*dir;

	path = ft_strdup("path/relative/toto/");
	split = ft_strsplit(path, '/');
	i = 0;
	if (path && path[0] == '/')
		dir = ft_strdup("/");
	else
		dir = ft_strnew(0);
	if (dir && dir[0] && access(dir, F_OK) == -1)
		printf("ERROR\n");
	else
		printf("OK\n");
	while (split && split[i] && (split[i + 1] || path[ft_strlen(path) - 1] == '/'))
	{
		printf("split[%d] = [%s]\n", i, split[i]);
		dir = ft_strapp(dir, split[i]);
		printf("test dir = [%s]\n", dir);
		if (access(dir, F_OK) == -1)
			printf("ERROR\n");
		else
			printf("OK\n");
		if (path[ft_strlen(dir)] == '/') // Peut etre mettra ca avant les tests
			dir = ft_strapp(dir, "/");
		i++;
	}
}
