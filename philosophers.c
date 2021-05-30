/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/30 12:45:59 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void think_func(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&state->write_mutex);
	write(1, "THINKING   ", 9);
	ft_putnbr_fd(philo->id, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_mutex[philo->rfork]);
	write(1, "Takes forks  ", 14);
	ft_putnbr_fd(philo->id, 1);
	write(1, "\n", 1);
	pthread_mutex_lock(&philo->state->forks_mutex[philo->lfork]);
}

void	drops_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->lfork]);
}

void *myfunc(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *) philo_;
	while (1)
	{
		think_func(philo->state, philo);
		take_forks(philo);
		// eat_func();
		drops_forks(philo);
		// sleep_func();
	}
	return NULL;
}

int start_threads(t_state *state)
{
	pthread_t t[state->num_of_philo];
	int i = 0;

	while (i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		i++;
	}
	i = 0;
	while (i < state->num_of_philo)
	{
		pthread_join(t[i], NULL);
		i++;
	}
	return (0);
}

t_philo *init_philo(t_state *state)
{
	t_philo *philo;
	int i;

	philo = malloc(sizeof(t_philo) * state->num_of_philo);
	i = 0;
	if (!philo)
		return (NULL);
	while (i < state->num_of_philo)
	{
		philo[i].id = i;
		philo[i].rfork = i;
		philo[i].lfork = (i + 1) % state->num_of_philo;
		philo[i].state = state;
		i++;
	}
	return (philo);
}

int init_state(t_state *state, char **argv, int argc)
{
	int i;

	i = 0;
	if ((state->num_of_philo = (int)ft_atoi(argv[1])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((state->time_to_die = ft_atoi(argv[2])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((state->time_to_eat = ft_atoi(argv[3])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((state->time_to_sleep = ft_atoi(argv[4])) == 0)
		return (exit_error("error: bad arguments\n"));
	if (argc == 5)
		state->notepme = -1;
	else if ((state->notepme = ft_atoi(argv[5])) == 0)
		return (exit_error("error: bad arguments\n"));
	state->forks_mutex = malloc(sizeof(pthread_mutex_t) * state->num_of_philo);
	while (i < state->num_of_philo)
	{
		pthread_mutex_init(&state->forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&state->write_mutex, NULL);
	state->philo = init_philo(state);
	return (0);
}

int main(int argc, char *argv[])
{
	t_state state;
	if (argc < 5 || argc > 6)
		return arguments_error();
	else
		init_state(&state, argv, argc);
	if (start_threads(&state))
		return (exit_error("error: in threads\n"));
	return (0);
}