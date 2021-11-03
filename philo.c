#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

static int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd ("(null)", 1));
	while (s[i])
		write (fd, &s[i++], 1);
	return (i);
}

int main (int argc, char *argv[])
{
	ft_putstr_fd(argv[0], argc);
	return (ft_putstr_fd("Wrong arguments\n", argc));
}
