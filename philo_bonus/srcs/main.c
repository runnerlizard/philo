#include "../include/philo_bonus.h"
/*
void *die_my_darling(void *ph)
{
	t_philo	*a;

	a = (t_philo *)ph;
	while (1)
	{
		if (a->ar->die_time < get_time() - a->last_meal)
		{
			message(a, " died\n");
			a->dead = 1;
			pthread_mutex_unlock(&a->ar->forks[a->r]);
			pthread_mutex_unlock(&a->ar->forks[a->id]);
			return (0);
		}
		if (a->meals == 0)
			return (0);
		usleep(5);
	}
	return(NULL);
}

static int	launch_threads(t_philo *p, t_args *a)
{
	int	i;

	i = 0;
	while (i < a->n)
	{
		p[i].id = i;
		if (i == a->n - 1)
			p[i].r = 0;
		else
			p[i].r = i + 1;
		p[i].dead = 0;
		p[i].meals = a->number;
		p[i].ar = a;
		if (pthread_create(&p[i].t, NULL, &activities, &p[i]) != 0)
		{
			free(a);
			free(p);
			return (- ft_putstr_fd("pthread_create error!\n", 1));
		}
		i++;
	}
	return (i);
}
*/
static int launch_philos(t_args *ph)
{
	t_args	*a;
	int		i;
	
	i = -1;
	while (++i < a->n)
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("new fork\n", 1);
		child_pid[i] = fork();
		if (child_pid[i] == 0)
		{
			ft_putnbr_fd(child_pid[i], 1);
			ft_putstr_fd("hello\n", 1);
			return (0);
		}
		else if (child_pid[i] > 0)
		{
			ft_putnbr_fd(child_pid[i], 1);
			ft_putstr_fd("hello\n", 1);
			return (0);
		}
		else
		{
			free(a);
			return (ft_putstr_fd("Fork error1\n", 1));
		}
	}
	return (0);
	 
}

static int check_create_args(int argc, char **argv, t_args *a)
{	
	if ((argc != 6) && (argc != 5))
		return (ft_putstr_fd("Invalid arguments number. Must be 5 or 4\n", 1));
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]) * 1000;
	a->eat_time = ft_atoi(argv[3]) * 1000;
	a->sleep_time = ft_atoi(argv[4]) * 1000;
	a->number = -1;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0) || (a->sleep_time < 0) || ( (argc == 6) && (a->number < 0)))
		return (ft_putstr_fd("Invalid arguments.\n", 1));
	a->forks = sem_open("/forks", O_CREAT, 0664, a->n);
	if (a->forks == SEM_FAILED)
		return (ft_putstr_fd("Semaphore error.\n", 1));
	get_time();
	return (0);
}

int main (int argc, char *argv[])
{
	t_args	*a;
	pid_t	main_pid;
	pid_t	*child_pid;
	int		i;
	
	child_pid = malloc(sizeof(pid_t) * a->n);
	a = malloc(sizeof(t_args));
	if (a == NULL)
		return (ft_putstr_fd("Malloc error1\n", 1));
	if (check_create_args(argc, argv, a) != 0)
	{
		free(a);
		return (1);
	}
	i = 0;
	main_pid = fork();
	if (main_pid == 0)
	{
		while (i < a->n)
		{
			fork
		}
	}
	else if (main_pid > 0)
	{
		i = 0;
		while (i++ < a->n)
			if (wait(NULL) != -1)
			{
				sem_destroy(a->forks);
				free(a);
				return (0);
			}
		sem_destroy(a->forks);
		free(a);
		return (1);
	}
	else 
	{
		sem_destroy(a-> forks);
		free(a);
		return (ft_putstr_fd("Fork error1\n", 1));
	}
}
