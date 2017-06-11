#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main(int ac, char **av)
{
	char	path[256];

	(void)ac;
	if (chdir(av[1]) == -1)
		printf("%s\n", strerror(errno));
	getcwd(path, 256);
	printf("test = [%s]\n", path);
	return (0);
}
