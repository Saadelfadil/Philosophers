/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/02 12:01:49 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time_stamp()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void think_func(t_state *state, t_philo *philo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&state->write_mutex);
	// printf("%lld %d THINKING\n", (get_time_stamp()), philo->id);
	ft_putnbr_fd((int)(get_time_stamp() / 1000), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "THINKING   ", 9);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
}

void take_forks(t_state *state, t_philo *philo)
{
	struct timeval time;

	pthread_mutex_lock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_lock(&state->write_mutex);
	gettimeofday(&time, NULL);
	// printf("%lld %d Takes forks\n", (get_time_stamp()), philo->id);
	ft_putnbr_fd((int)(get_time_stamp() / 1000), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "Take right fork", 15);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
	pthread_mutex_lock(&philo->state->forks_mutex[philo->lfork]);
	pthread_mutex_lock(&state->write_mutex);
	gettimeofday(&time, NULL);
	// printf("%lld %d Takes forks\n", (get_time_stamp()), philo->id);
	ft_putnbr_fd((int)(get_time_stamp() / 1000), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "Take left fork", 14);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
}

void drops_forks(t_philo *philo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->state->write_mutex);
	// printf("%lld %d philosopher is sleeping\n", (get_time_stamp()), philo->id);
	ft_putnbr_fd((int)(get_time_stamp() / 1000), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is sleeping ", 24);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->state->write_mutex);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->lfork]);
}

void sleep_func(t_state *state, t_philo *philo)
{
	long long start = get_time_stamp();
	// pthread_mutex_lock(&state->write_mutex);
	// printf("%lld %d philosopher is sleeping\n", (get_time_stamp()), philo->id);
	// write(1, "philosopher is sleeping ", 24);
	// ft_putnbr_fd(philo->id, 1);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&state->write_mutex);
	usleep(state->time_to_sleep * 1000 - 20000);
	while (get_time_stamp() - start < state->time_to_sleep);
}

void eat_func(t_state *state, t_philo *philo)
{
	long long start = get_time_stamp();
	pthread_mutex_lock(&state->write_mutex);
	// printf("%lld %d philosopher is eating\n", (get_time_stamp()), philo->id);
	ft_putnbr_fd((int)(get_time_stamp() / 1000), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is eating ", 23);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
	usleep(state->time_to_eat * 1000 - 20000);
	while (get_time_stamp() - start < state->time_to_eat);
}

void *myfunc(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		think_func(philo->state, philo);
		take_forks(philo->state, philo);
		eat_func(philo->state, philo);
		drops_forks(philo);
		sleep_func(philo->state, philo);
	}
	return NULL;
}

int start_threads(t_state *state)
{
	pthread_t t[state->num_of_philo];
	int i = -1;

	while (++i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		i += 2;
	}
	usleep(800);
	i = 0;
	while (++i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		i += 2;
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
		philo[i].id = i + 1;
		philo[i].rfork = ((i + 1) + 1) % state->num_of_philo;
		philo[i].lfork = i + 1;
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