/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/16 15:57:52 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_logger(int status, long time, int id, t_state *state)
{
	static int	check;

	pthread_mutex_lock(&(state->write_mutex));
	if (!check)
	{
		ft_putlong_fd(time, 1);
		ft_putstr_fd(" ", 1);
		ft_putlong_fd(id, 1);
		if (status == 1)
			ft_putstr_fd(" \x1B[32mis eating\x1B[0m\n", 1);
		else if (status == 2)
			ft_putstr_fd(" \x1B[33mis sleeping\x1B[0m\n", 1);
		else if (status == 3)
			ft_putstr_fd(" \x1B[34mis thinking\x1B[0m\n", 1);
		else if (status == 7)
		{
			check = 1;
			write(1, "philosopher is died\n", 20);
		}
		else if (status == 4)
			ft_putstr_fd(" \x1B[35mhas taken a fork\x1B[0m\n", 1);
	}
	pthread_mutex_unlock(&(state->write_mutex));
}

int	start_threads(t_state *state)
{
	pthread_t	*t;
	pthread_t	t_eat_count;
	int			i;

	i = 1;
	t = (pthread_t *)malloc(sizeof(pthread_t) * state->num_of_philo);
	state->start = get_time_stamp();
	if (state->notepme != -1)
		pthread_create(&t_eat_count, NULL, &eat_counter, (void *)state);
	while (i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		usleep(800);
		i += 2;
	}
	i = 0;
	while (i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		usleep(800);
		i += 2;
	}
	pthread_mutex_lock(&state->exit_mutex);
	return (0);
}

t_philo	*init_philo(t_state *state)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * state->num_of_philo);
	i = 0;
	if (!philo)
		return (NULL);
	while (i < state->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].rfork = (i + 1) % state->num_of_philo;
		philo[i].lfork = i;
		philo[i].state = state;
		philo[i].last_time_eat = (int)(get_time_stamp());
		pthread_mutex_init(&philo[i].mutex, NULL);
		pthread_mutex_init(&philo[i].eat_count, NULL);
		i++;
	}
	return (philo);
}

int	init_state(t_state *state, char **argv, int argc)
{
	int	i;

	i = 0;
	state->num_of_philo = (int)ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		state->notepme = -1;
	else if (argc == 6)
		state->notepme = ft_atoi(argv[5]);
	ft_show_error(state, argc);
	state->forks_mutex = malloc(sizeof(pthread_mutex_t) * state->num_of_philo);
	while (i < state->num_of_philo)
		pthread_mutex_init(&state->forks_mutex[i++], NULL);
	pthread_mutex_init(&(state->write_mutex), NULL);
	pthread_mutex_init(&state->exit_mutex, NULL);
	pthread_mutex_lock(&state->exit_mutex);
	state->philo = init_philo(state);
	state->alive = 1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_state	state;

	if (argc < 5 || argc > 6)
		return (arguments_error());
	else
		init_state(&state, argv, argc);
	if (start_threads(&state))
		return (exit_error("error: in threads\n"));
	return (0);
}
