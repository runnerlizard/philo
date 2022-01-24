#include "../include/philo_bonus.h"

void *die_my_darling(void *ph)
{
	t_args	*a;

	a = (t_args *)ph;
	while (1)
	{
		if (a->die_time < get_time() - a->last_meal)
		{
			message(a, " died\n");
			sem_close(a->send_mes);
			sem_close(a->forks);
			free(a->pid);
			free(a);
			exit (1);
		}
		if (a->meals == 0)
			return (NULL);
		usleep(5);
	}
	return(NULL);
}


static t_args *check_create_args(int argc, char **argv)
{	
	t_args	*a;

	if ((argc != 6) && (argc != 5))
		return (NULL);
	a = malloc(sizeof(t_args));
	if (a == NULL)
		return (NULL);
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]) * 1000;
	a->eat_time = ft_atoi(argv[3]) * 1000;
	a->sleep_time = ft_atoi(argv[4]) * 1000;
	a->number = -1;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0) || (a->sleep_time < 0) || ( (argc == 6) && (a->number < 0)))
		return (NULL);
	sem_unlink("forks");
	sem_unlink("send_mes");
	a->send_mes = sem_open("send_mes", O_CREAT, 0664, 1);
	a->forks = sem_open("forks", O_CREAT, 0664, a->n);
	if ((a->forks == SEM_FAILED) || (a->send_mes == SEM_FAILED))
		return (NULL);
	a->meals = a->number;
	get_time();
	return (a);
}

static void	launch_child(t_args *ph)
{
	t_args	*a;
	int		i;

	a = ph;
	a->pid = malloc(sizeof(pid_t) * a->n);
	if (a->pid == NULL)
	{
		free(a);
		ft_putstr_fd("Malloc error\n", 1);
		exit (1);
	}
	i = -1;
	while (++i < a->n)
	{
		a->pid[i] = fork();
		if (a->pid[i] < 0)
			i--;
		else if (a->pid[i] == 0)
		{
			a->id = i;
			break ;
		}
	}
}

int main (int argc, char *argv[])
{
	t_args	*a;
	int		i;
	pid_t	pid1;
	
	a = check_create_args(argc, argv);
	if (a == NULL)
		return (ft_putstr_fd("Args error\n", 1));
	launch_child(a);
	if (a->pid[a->id] == 0)
		activities(a);
	else
	{
		pid1 = waitpid(-1, NULL, 0);
		usleep(a->eat_time * 2 + 1000);
		i = -1;
		while (++i < a->n)
			if (a->pid[i] != pid1)
				kill(a->pid[i], SIGTERM);
		sem_unlink("send_mes");
		sem_unlink("forks");
		free(a->pid);
		free(a);
	}
	return (0);
}
