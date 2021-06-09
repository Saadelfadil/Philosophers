/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:05:18 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/07 18:51:14 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

typedef struct s_state
{
	int     num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	notepme;
	long	long start;
	sem_t	*write_mutex;
	sem_t	*forks_mutex;
	sem_t	*exit_mutex;
	struct s_philo *philo;
} t_state;

typedef struct s_philo
{
	int			id;
	int			lfork;
	int			rfork;
	long long	last_time_eat;
	long long	limit;
	int			is_eating;
	sem_t			*mutex;
	sem_t			*eat_count;
	struct s_state	*state;
} t_philo;

long	ft_atoi(const char *str);
int		arguments_error();
int		ft_strlen(char const *str);
int		exit_error(char const *str);
void	ft_putlong_fd(long long n, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif