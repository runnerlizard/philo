#include "ft_printf.h"

int	ft_putpercent(char c)
{
	char	percent;
	int		j;

	percent = '%';
	if ((c == 'i') || (c == 'd') || (c == 'c') || (c == 's') || (c == 'p')
		|| (c == 'u') || (c == 'x') || (c == 'X'))
		return (0);
	j = 0;
	if (c == '%')
	{
		j = j + write (1, &c, 1);
		return (1);
	}
	else
	{
		j = j + write (1, &percent, 1);
		j = j + write (1, &c, 1);
		return (2);
	}
}

int	ft_putchar(int n)
{
	return (write(1, &n, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;
	int		j;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd ("(null)", 1));
	while (s[i])
		j = j + write (fd, &s[i++], 1);
	return (i);
}

int	ft_count (int d)
{
	static int	count;
	int			tmp;

	tmp = 0;
	if (d == -1)
	{
		tmp = count;
		count = 0;
		return (tmp);
	}
	count = count + d;
	return (count);
}
