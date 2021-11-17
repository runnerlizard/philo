#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*substring;

	size = ft_strlen(s);
	if (size < start)
		size = 0;
	else if (size < start + len)
		size = size - start;
	else
		size = len + 1;
	substring = (char *)malloc(size * sizeof(char));
	if (substring == NULL)
		return (NULL);
	i = 0;
	if ((start >= ft_strlen(s)) || (len == 0))
		substring[0] = 0;
	while ((i + start < ft_strlen(s)) && (i < len))
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = 0;
	return (substring);
}
