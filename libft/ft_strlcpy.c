#include "libft.h"

size_t	ft_strlcpy (char *dst, const char *src, size_t l)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (src[res])
		res++;
	if (l == 0)
	{
		while (dst[i])
			i++;
		dst[i] = 0;
		return (res);
	}
	while (((i + 1) < l) && (i < res))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (res);
}
