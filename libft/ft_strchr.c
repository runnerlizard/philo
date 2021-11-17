#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (c > 256)
		c = c - 256;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i++;
	}
	if ((c == 0) & (str[i] == 0))
		return ((char *)&str[i]);
	return (NULL);
}
