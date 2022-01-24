/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Cluco <cluco@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:22:45 by Cluco             #+#    #+#             */
/*   Updated: 2022/01/24 17:24:54 by Cluco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_args
{
	int			n;
	long int	die_time;
	long int	eat_time;
	long int	sleep_time;
	int			number;
	sem_t		*send_mes;
	sem_t		*forks;
	int			id;
	int			meals;
	long int	last_meal;
	pthread_t	die_check;
	pid_t		*pid;
}				t_args;

int			ft_atoi(char const *str);
int			message(t_args *ph, char *str);
int			ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(long int n, int fd);
size_t		ft_strlen(const char *str);
long int	get_time(void);
void		*activities(t_args *ph);
void		*die_my_darling(void *ph);

#endif
