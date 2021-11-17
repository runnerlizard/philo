#include "ft_printf.h"

void	ft_write_hex(unsigned long d, int registr)
{
	char	c;

	if (d > 9)
	{
		if (registr == 1)
			c = d + 87;
		else
			c = d + 55;
	}
	else
		c = d + 48;
	registr = registr + write(1, &c, 1);
}

int	ft_hex_length(unsigned long n)
{
	int	i;

	i = 1;
	while (n > 15)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_hex (unsigned long n, int registr)
{
	unsigned long			d;
	int						i;
	int						j;
	int						count;

	d = n;
	i = ft_hex_length(d);
	count = i;
	while (i >= 1)
	{
		j = i;
		d = n;
		while (j > 1)
		{
			d = d / 16;
			j--;
		}
		d = d % 16;
		ft_write_hex (d, registr);
		i--;
	}
	return (count);
}

int	ft_print_p (unsigned long p)
{
	int			count;

	count = ft_putstr_fd ("0x", 1) + ft_hex(p, 1);
	return (count);
}

int	ft_printf (const char *input, ...)
{
	int			i;
	va_list		vl;

	va_start (vl, input);
	i = 0;
	while (input[i])
	{
		while ((input[i] != '%') && (input[i]))
			ft_count(ft_putchar(input[i++]));
		if (input[i] == '%')
		{
			if ((input[i + 1] == 'd') || (input[i + 1] == 'i')
				|| (input[i + 1] == 'c'))
				ft_count(ft_hub_int(input[i + 1], va_arg(vl, int)));
			else if (input[i + 1] == 's')
				ft_count(ft_putstr_fd(va_arg(vl, char *), 1));
			else if ((input[i + 1] == 'p') || (input[i + 1] == 'u')
				|| (input[i + 1] == 'x') || (input [i + 1] == 'X'))
				ft_count(fl(input[i + 1], va_arg(vl, unsigned long)));
			ft_count(ft_putpercent(input[i + 1]));
			i = i + 2;
		}
	}
	va_end (vl);
	return (ft_count(-1));
}
