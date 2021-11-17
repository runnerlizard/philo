#include "libft.h"

void	*ft_memccpy (void *dest, const void *src, int ch, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while ((i < n) & ((((unsigned char *)src)[i]) != (unsigned char)ch))
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (i >= n)
		return (NULL);
	else
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (&(((unsigned char *)dest)[i + 1]));
}
