#include <stdio.h>
#include <unistd.h>

int	recur(int nb_tok)
{
	static int i = 0;

	i++;
	printf("result = %d\n", 2 * i - (i - 1));
	sleep(4);
	recur(nb_tok);
	return (1);
}

int main(void)
{
	int	nb_tok;

	nb_tok = 2;
	recur(nb_tok);
	return (1);
}
