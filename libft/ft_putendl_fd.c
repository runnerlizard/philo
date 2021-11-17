#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;
	char	c;
	int		j;

	i = 0;
	j = 0;
	c = '\n';
	while (s[i])
		j = j + write (fd, &s[i++], 1);
	j = j + write (fd, &c, 1);
}
