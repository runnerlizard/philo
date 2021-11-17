#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (s2[0] == '\0')
		return ((char *)s1);
	j = 0;
	while ((j < n) && (s1[j]))
	{
		i = 0;
		while ((j < n) && (s2[i]) && (s1[j]) && (s2[i] == s1[j]))
		{
			++i;
			++j;
		}
		if (s2[i] == '\0')
			return ((char *)&s1[j - i]);
		j = j - i + 1;
	}
	return (0);
}
