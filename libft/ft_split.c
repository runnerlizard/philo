#include "libft.h"

size_t	ft_split_count(char const *str, char ch)
{
	size_t	i;
	size_t	res;
	size_t	k;

	i = 0;
	res = 0;
	while (str[i])
	{
		k = 0;
		while (str[i] == ch)
			i++;
		while ((str[i] != ch) && (str[i]))
		{
			i++;
			k++;
		}
		if (k != 0)
			res++;
	}
	return (res);
}

void	ft_write_word(char *res, char const *str, size_t start, size_t end)
{
	size_t	n;

	n = 0;
	while (start < end)
		res[n++] = str[start++];
	res[n] = '\0';
}

size_t	set_start_i(char const *str, size_t i, char ch, int flag)
{
	int	l;

	l = i;
	if (flag == 1)
	{	
		while (str[l] == ch)
			l++;
		return (l);
	}
	else
	{
		while ((str[l] != ch) && (str[l]))
			l++;
		return (l);
	}
}

char	**split_free(char **res)
{
	size_t	j;

	j = 0;
	while (res[j])
	{
		free(res[j]);
		j++;
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *str, char ch)
{
	char	**res;
	size_t	start;
	size_t	i;
	size_t	j;

	if (!(str))
		return (NULL);
	res = (char **)malloc((sizeof(char *)) * (ft_split_count(str, ch) + 1));
	if (res == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (str[i])
	{
		start = set_start_i(str, i, ch, 1);
		i = set_start_i(str, start, ch, 2);
		if (start != i)
			res[j] = (char *)malloc(sizeof(char) * (i - start + 1));
		if ((res[j] == NULL) && (i != start))
			return (split_free (res));
		if (start != i)
			ft_write_word(res[j++], str, start, i);
	}
	res[j] = (void *)0;
	return (res);
}
