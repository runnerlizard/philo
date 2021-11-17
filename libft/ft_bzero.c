#include "libft.h"

void	ft_bzero(void *dest, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = 0;
		i++;
	}
}
