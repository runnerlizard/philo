#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t l)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (dst[i])
		i++;
	while ((j + i + 1 < l) && (src[j]))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
	while (src[j])
		j++;
	if (i > l)
		i = l;
	return (i + j);
}
