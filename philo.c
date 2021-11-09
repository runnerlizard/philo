#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void *routine(int num)
{
	printf("Test pthread  %d\n", num);
}

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
	pthread_t	t[ft_atoi(argv[1])];

	if (pthread_create(&t[i], NULL, &routine, i) != 0)
		return (ft_putstr_fd ("Thread creating error", 1));
	if (pthread_join(t[i], NULL) != 0)
		return (ft_putstr_fd ("Thread joining error", 1));
	return (0);
}
