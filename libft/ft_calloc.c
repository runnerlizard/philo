#include "libft.h"

void	*ft_calloc(size_t n, size_t s)
{
	char		*res;
	size_t		i;

	i = 0;
	res = (char *)malloc(n * s);
	if (res == NULL)
		return (NULL);
	else
		while (i < (n * s))
			res[i++] = 0;
	return (res);
}
