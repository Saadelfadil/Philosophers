/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/14 08:55:59 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time_stamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_sleep(long long ms)
{
	long long end = get_time_stamp() + ms;

	while (get_time_stamp() < end)
		usleep(50);
}

void think_func(t_state *state, t_philo *philo)
{
	// struct timeval	time;

	// gettimeofday(&time, NULL);
	// pthread_mutex_lock(&(state->write_mutex));
	// ft_putlong_fd((get_time_stamp()), 1);
	// ft_putlong_fd(philo->id, 1);
	// write(1, "THINKING   ", 9);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&(state->write_mutex));
	ft_logger(3, get_time_stamp(), philo->id, state);
}

void take_forks(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_lock(&philo->state->forks_mutex[philo->lfork]);
	// pthread_mutex_lock(&(state->write_mutex));
	// ft_putlong_fd((get_time_stamp()), 1);
	// ft_putlong_fd(philo->id, 1);
	// write(1, "Take forks", 11);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&(state->write_mutex));
	ft_logger(4, get_time_stamp(), philo->id, state);
}

void drops_forks(t_philo *philo)
{
	// struct timeval	time;
	// if (!philo->state->alive)
	// 	return ;
	// gettimeofday(&time, NULL);
	// pthread_mutex_lock(&((philo->state->write_mutex)));
	// printf("mutex sleeping %p\n", &philo->(state->write_mutex));
	// ft_putlong_fd((get_time_stamp()), 1);
	// ft_putlong_fd(philo->id, 1);
	// write(1, "philosopher is sleeping ", 24);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&((philo->state->write_mutex)));
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->lfork]);
}

void sleep_func(t_state *state)
{

	ft_logger(2, get_time_stamp(), state->philo->id, state->philo->state);
	ft_sleep(state->time_to_sleep);
}

void eat_func(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	// pthread_mutex_lock(&(state->write_mutex));

	// printf("mutex eating %p\n", &(state->write_mutex));
	philo->last_time_eat = (get_time_stamp());
	philo->limit = philo->last_time_eat + state->time_to_die;
	philo->is_eating = 1;
	ft_logger(1, get_time_stamp(), philo->id, state);
	// ft_putlong_fd(philo->last_time_eat, 1);
	// ft_putlong_fd(philo->id, 1);
	// write(1, "philosopher is eating ", 23);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&(state->write_mutex));
	pthread_mutex_unlock(&philo->mutex);
	ft_sleep(state->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat_count);
}

void ft_putstr_fd(char *s, int i)
{
	i = 1;
	int len = ft_strlen(s);
	write(1, s, len);
}

void ft_logger(int status, long time, int id, t_state *state)
{
	static int check;

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

void *supervisor(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *)philo_;
	while (philo->state->alive)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time_stamp() > philo->limit)
		{
			ft_logger(7, get_time_stamp(), philo->id, philo->state);
			philo->state->alive = 0;
			pthread_mutex_unlock(&philo->state->exit_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(8000);
	}
	return (NULL);
}

void *eat_counter(void *state_)
{
	t_state *state;
	int i;
	int j;

	i = 0;
	state = (t_state *)state_;
	t_philo *philo = state->philo;
	while (i <= state->notepme)
	{
		j = 0;
		while (j < state->num_of_philo)
		{
			pthread_mutex_lock(&philo[j].eat_count);
			j++;
		}
		i++;
	}
	pthread_mutex_lock(&(state->write_mutex));
	printf("DONE\n");
	pthread_mutex_unlock(&state->exit_mutex);
	return (NULL);
}

void *myfunc(void *philo_)
{
	t_philo *philo;
	pthread_t t_id;

	philo = (t_philo *)philo_;
	philo->last_time_eat = (long)get_time_stamp();
	philo->limit = philo->last_time_eat + philo->state->time_to_die;
	philo->is_eating = 0;
	philo->state->alive = 1;
	pthread_create(&t_id, NULL, &supervisor, philo_);

	while (philo->state->alive)
	{
		think_func(philo->state, philo);
		take_forks(philo->state, philo);
		eat_func(philo->state, philo);
		drops_forks(philo);
		sleep_func(philo->state);
	}
	return (NULL);
}

int start_threads(t_state *state)
{
	pthread_t t[state->num_of_philo];
	pthread_t t_eat_count;
	int i = 1;

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
		philo[i].last_time_eat = (int)(get_time_stamp());
		pthread_mutex_init(&philo[i].mutex, NULL);
		pthread_mutex_init(&philo[i].eat_count, NULL);
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
	// if (state->num_of_philo < 2)
	// 	ft_logger(7, get_time_stamp(), state->philo->id, state->philo->state);
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
		pthread_mutex_init(&state->forks_mutex[i++], NULL);
	pthread_mutex_init(&(state->write_mutex), NULL);
	pthread_mutex_init(&state->exit_mutex, NULL);
	pthread_mutex_lock(&state->exit_mutex);
	state->philo = init_philo(state);
	state->alive = 1;
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