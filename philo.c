#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

int	ft_atoi(const char *str)
{
	size_t	i;
	size_t	a;
	int		sign;

	i = 0;
	sign = 1;
	a = 0;
	while (((str[i] >= 9) && (str[i] <= 13)) || (str[i] == ' '))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= 48) & (str[i] <= 57) & (a < 9999999999))
	{
		a = (a * 10) + (str[i] - 48);
		i++;
	}
	if ((a > 2147483648) && (sign == -1))
		return (0);
	if ((a > 2147483648) || ((a == 2147483648) & (sign == 1)))
		return (-1);
	return (a * sign);
}


static int check_args(int *i, int argc, char **argv)
{
	int	j;

	if ((argc != 6) && (argc != 5))
		return (printf("Invalid arguments number. Must be 5 or 4\n"));
	j = 0;
	while (argv[++j])
		if ((i[j - 1] = ft_atoi(argv[j])) <= 0)
			return (printf("Invalid argument: %s. Must be positive number\n", argv[j]));
	return (0);
}

void	*routine()
{
	printf("Test\n");
	return (NULL);
}

int main (int argc, char *argv[])
{
	int			*i;
	int 		j;
	pthread_t	t1;

	if ((i = (int *)malloc(sizeof(int) * argc)) == NULL)
		return (printf("Malloc error.\n"));
	if ((j = check_args(i, argc, argv)) != 0){
		printf("%d\n", j);
		return (0);
	}
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (printf("pthread_create error!\n"));
	if (pthread_join(t1, NULL) != 0)
		return (printf("pthread_join error!\n"));
	j = 0;
	while (i[j])
		printf("%d\n", i[j++]);
	return (argc);
}
