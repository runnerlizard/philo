#include "../include/philo_bonus.h"

void *die_my_darling(void *ph)
{
	t_args	*a;
	int		i;

	a = (t_args *)ph;
	while (a->dead == 0)
	{
		if (a->die_time < get_time() - a->last_meal)
		{
			message(a, " died\n");
			i = 0;
			usleep(a->die_time);
			while (i < a->n * 5)
			{
				sem_post(a->forks);
				sem_post(a->send_mes);
				usleep(1000);
			}
			ft_putstr_fd("finish7\n", 1);
			break;
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
	a-> dead = 0;
	get_time();
	return (a);
}

int main (int argc, char *argv[])
{
	t_args	*a;
	int		i;
	
	a = check_create_args(argc, argv);
	if (a == NULL)
		return (ft_putstr_fd("Args error\n", 1));
	a->pid = malloc(sizeof(pid_t) * a->n);
	if (a->pid == NULL)
	{
		free(a);
		return (ft_putstr_fd("Malloc error\n", 1));
	}
	i = -1;
	while (++i < a->n)
	{
		a->pid[i] = fork();
		if (a->pid[i] < 0)
			return (1);
		if (a->pid[i] == 0)
		{
			a->id = i;
			break ;
		}
	}
	if (a->pid[a->id] == 0)
		activities(a);
	else
	{
		while (waitpid(-1, NULL, 0) > 0)
			ft_putstr_fd("finish\n", 1);	
		sem_unlink("send_mes");
		sem_unlink("forks");
		free(a->pid);
		free(a);
		ft_putstr_fd("here\n", 1);
	}
	return (0);
}
