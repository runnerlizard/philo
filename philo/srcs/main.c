/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cluco <cluco@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:21:43 by Cluco             #+#    #+#             */
/*   Updated: 2022/01/25 09:56:54 by Cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*die_my_darling(void *ph)
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
	return (NULL);
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
			return (-ft_putstr_fd("pthread_create error!\n", 1));
		}
		i++;
	}
	return (i);
}

static int	check_create_args(int argc, char **argv, t_args *a)
{
	int	i;

	if ((argc != 6) && (argc != 5))
		return (ft_putstr_fd("Invalid arguments number. Must be 5 or 4\n", 1));
	a->n = ft_atoi(argv[1]);
	a->die_time = ft_atoi(argv[2]) * 1000;
	a->eat_time = ft_atoi(argv[3]) * 1000;
	a->sleep_time = ft_atoi(argv[4]) * 1000;
	a->number = -2;
	if (argc == 6)
		a->number = ft_atoi(argv[5]);
	if ((a->n < 1) || (a->die_time < 0) || (a->eat_time < 0)
		|| (a->sleep_time < 0) || ((argc == 6) && (a->number == -1)))
		return (ft_putstr_fd("Invalid arguments.\n", 1));
	a->send_mes = 1;
	i = 0;
	a->forks = malloc(sizeof(pthread_mutex_t) * a->n);
	if (a->forks == NULL)
		return (ft_putstr_fd("Malloc error\n", 1));
	while (i < a->n)
		pthread_mutex_init(&a->forks[i++], NULL);
	get_time();
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	*a;
	t_philo	*p;
	int		i;

	a = malloc(sizeof(t_args));
	if (a == NULL)
		return (ft_putstr_fd("Malloc error1\n", 1));
	if (check_create_args(argc, argv, a) != 0)
		return (1);
	p = malloc(sizeof(t_philo) * a->n);
	if (p == NULL)
		return (ft_putstr_fd("Malloc error2\n", 1));
	i = launch_threads(p, a);
	if (i < 0)
		return (1);
	while (--i >= 0)
	{
		pthread_join(p[i].t, NULL);
		pthread_mutex_destroy(&a->forks[i]);
	}
	free(a->forks);
	free(a);
	free(p);
	return (argc);
}
