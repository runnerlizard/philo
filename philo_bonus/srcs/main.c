/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cluco <cluco@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:22:36 by Cluco             #+#    #+#             */
/*   Updated: 2022/01/26 15:31:11 by Cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	*die_my_darling(void *ph)
{
	t_args	*a;

	a = (t_args *)ph;
	while (1)
	{
		if (a->die_time < get_time() - a->last_meal)
		{
			a->last_meal = -1;
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
	return (NULL);
}

static void	free_exit(t_args *a, char *code)
{
	int	i;

	i = 0;
	while (code[i] != 0)
	{
		if (code[i] == '1')
			free(a);
		else if (code[i] == '2')
			sem_unlink("forks");
		else if (code[i] == '3')
			sem_unlink("send_mes");
		else if (code[i] == '4')
			free(a->pid);
		else if (code[i] == '0')
			exit (1);
		i++;
	}
}

static t_args	*check_create_args(int argc, char **argv)
{
	t_args	*a;

	if ((argc != 6) && (argc != 5))
		return (NULL);
	a = malloc(sizeof(t_args));
	if (a == NULL)
		exit (1);
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]) * 1000;
	a->eat_time = ft_atoi(argv[3]) * 1000;
	a->sleep_time = ft_atoi(argv[4]) * 1000;
	a->number = -2;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0)
		|| (a->sleep_time < 0) || ((argc == 6) && (a->number == -1)))
		free_exit(a, "10");
	free_exit(a, "23");
	a->forks = sem_open("forks", O_CREAT, 0664, a->n);
	if (a->forks == SEM_FAILED)
		free_exit(a, "10");
	a->send_mes = sem_open("send_mes", O_CREAT, 0664, 1);
	if (a->send_mes == SEM_FAILED)
		free_exit(a, "130");
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
		ft_putstr_fd("Malloc error\n", 1);
		free_exit(a, "1230");
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

int	main(int argc, char *argv[])
{
	t_args	*a;
	int		i;
	pid_t	pid1;

	a = check_create_args(argc, argv);
	if (a == NULL)
		return (ft_putstr_fd("Args error\n", 1));
	get_time();
	a->meals = a->number;
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
		free_exit(a, "41230");
	}
	return (0);
}
