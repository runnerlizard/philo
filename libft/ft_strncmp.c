#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	i;

	i = 0;
	while (i < n)
	{
		diff = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (diff > 0)
			return (1);
		else if (diff < 0)
			return (-1);
		else if ((s1[i] == 0) & (s2[i] == 0))
			return (0);
		i++;
	}
	return (0);
}
