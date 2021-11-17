#include "libft.h"
#include <stdio.h>
#include <string.h>

int	ft_strtrimcmp(char const c, char const *set)
{
	size_t	j;
	int		k;

	j = 0;
	k = 0;
	while ((set[j]) && (k == 0))
	{
		if (c == set[j])
			k = 1;
		j++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*res;

	i = 0;
	j = 0;
	if (s1[0] != 0)
	{
		while ((ft_strtrimcmp(s1[i], set) == 1) && (i < ft_strlen(s1)))
			i++;
		j = ft_strlen(s1) - 1;
		while ((ft_strtrimcmp(s1[j], set) == 1) && (j > 0))
			j--;
		if (i > j)
			j = i;
	}
	res = (char *)malloc((j - i + 2) * sizeof(char));
	if (res == NULL)
		return (NULL);
	k = 0;
	while (i <= j)
		res[k++] = s1[i++];
	res[k] = 0;
	return (res);
}
