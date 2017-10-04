#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	unsigned int 	div;
	unsigned int	nb;
	int 			size;
	char			*result;
	int				sign;
	unsigned int	curs;
	char			tab_hexa[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	div = 1;
	size = 1;
	sign = 0;
	if (value < 0)
	{
		nb = -value;
		if (base == 10)
		{
			sign = 1;
			size++;
		}
	}
	else
		nb = value;
	while (nb / base >= div)
	{
		div *= base;
		size++;
	}
	if (!(result = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	result[size + 1] = '\0';
	while (size + sign > 0)
	{
		curs = 0;
		if (sign == 1 && base == 10)
			result[0] = '-';
		while (curs < nb % base)
			curs++;
		result[size - 1] = tab_hexa[curs];
		nb /= base;
		size--;
	}
	return (result);
}
