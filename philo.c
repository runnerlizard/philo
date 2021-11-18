#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include "libft.h"
#include "ft_printf.h"

static void check_args(int *i, int argc, char **argv)
{
	int	j;

	if (argc != 6)
		exit (ft_printf("Invalid arguments number. Must be 5\n"));
	j = 0;
	while (argv[++j])
		if ((i[j - 1] = ft_atoi(argv[j])) <= 0)
			exit (ft_printf("Invalid argument: %s. Must be positive number\n", argv[j]));
}

void	*routine()
{
	ft_printf("Test\n");
	return (NULL);
}

int main (int argc, char *argv[])
{
	int			*i;
	int 		j;
	pthread_t	t1;

	if ((i = (int *)malloc(sizeof(int) * argc)) == NULL)
		exit (ft_printf("Malloc error.\n"));
	check_args(i, argc, argv);
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	j = 0;
	while (i[j])
		ft_printf("%d\n", i[j++]);
	return (argc);
}
