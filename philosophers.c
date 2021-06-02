/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/02 17:14:12 by sel-fadi         ###   ########.fr       */
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
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "THINKING   ", 9);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
}

void take_forks(t_state *state, t_philo *philo)
{
	struct timeval time;

	pthread_mutex_lock(&philo->state->forks_mutex[philo->rfork]);
	// pthread_mutex_lock(&state->write_mutex);
	// gettimeofday(&time, NULL);
	// printf("%lld %d Takes forks\n", (get_time_stamp()), philo->id);
	// ft_putlong_fd(get_time_stamp(), 1);
	// ft_putnbr_fd(philo->id, 1);
	// write(1, "Take right fork", 15);
	// write(1, "\n", 1);
	// pthread_mutex_unlock(&state->write_mutex);
	pthread_mutex_lock(&philo->state->forks_mutex[philo->lfork]);
	pthread_mutex_lock(&state->write_mutex);
	// gettimeofday(&time, NULL);
	// printf("%lld %d Takes forks\n", (get_time_stamp()), philo->id);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "Take forks", 11);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
}

void drops_forks(t_philo *philo)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->state->write_mutex);
	// printf("%lld %d philosopher is sleeping\n", (get_time_stamp()), philo->id);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is sleeping ", 24);
	write(1, "\n", 1);
	pthread_mutex_unlock(&philo->state->write_mutex);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->lfork]);
}

void sleep_func(t_state *state, t_philo *philo)
{
	// long long start = get_time_stamp();
	usleep(state->time_to_sleep * 1000);
	// usleep(state->time_to_sleep * 1000 - 20000);
	// while (get_time_stamp() - start < state->time_to_sleep)
	// ;
}

void eat_func(t_state *state, t_philo *philo)
{
	// long long start = get_time_stamp();
	pthread_mutex_lock(&philo->mutex);
	pthread_mutex_lock(&state->write_mutex);
	philo->last_time_eat = (get_time_stamp());
	philo->limit = philo->last_time_eat + state->time_to_die;
	philo->is_eating = 1;
	ft_putlong_fd(philo->last_time_eat, 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is eating ", 23);
	write(1, "\n", 1);
	pthread_mutex_unlock(&state->write_mutex);
	pthread_mutex_unlock(&philo->mutex);
	// usleep(state->time_to_eat * 1000 - 20000);
	// while (get_time_stamp() - start < state->time_to_eat)
	// 	;
	usleep(state->time_to_eat * 1000);
	philo->is_eating = 0;
}

void *supervisor(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && get_time_stamp() > philo->limit)
		{
			pthread_mutex_lock(&philo->state->write_mutex);
			ft_putnbr_fd(philo->id, 1);
			write(1, "philosopher is died", 19);
			write(1, "\n", 1);
			pthread_mutex_unlock(&philo->state->write_mutex);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->exit_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mutex);
	}
	return (NULL);
}

// void	*eat_counter(void *philo_)
// {
// 	t_philo *philo;
// 	int i;
// 	int j;

// 	i = 0;
// 	philo = (t_philo *)philo_;
// 	if (philo->state->notepme != -1)
// 	{
// 		while (i < philo->state->notepme)
// 		{
// 			j = 0;
// 			while (j < philo->state->num_of_philo)
// 			{
// 				pthread_mutex_lock(&philo->eat_count);
// 				j++;
// 			}
// 			i++;
// 			pthread_mutex_unlock(&philo->eat_count);
// 		}
// 	}
// 	return (NULL);
// }

void *myfunc(void *philo_)
{
	t_philo *philo;
	pthread_t t_id;
	pthread_t t_eat_count;

	philo = (t_philo *)philo_;
	philo->last_time_eat = (long)get_time_stamp();
	philo->limit = philo->last_time_eat + philo->state->time_to_die;
	philo->is_eating = 0;
	pthread_create(&t_id, NULL, &supervisor, philo_);
	// pthread_create(&t_eat_count, NULL, &eat_counter, philo_);
	while (1)
	{
		think_func(philo->state, philo);
		take_forks(philo->state, philo);
		eat_func(philo->state, philo);
		drops_forks(philo);
		sleep_func(philo->state, philo);
	}
	return (NULL);
}

int start_threads(t_state *state)
{
	pthread_t t[state->num_of_philo];
	int i = -1;

	state->start = get_time_stamp();
	while (++i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		usleep(800);
		i += 2;
	}
	i = 0;
	while (++i < state->num_of_philo)
	{
		pthread_create(&t[i], NULL, &myfunc, &state->philo[i]);
		usleep(800);
		i += 2;
	}
	// i = 0;
	// while (i < state->num_of_philo)
	// {
	// 	pthread_join(t[i], NULL);
	// 	i++;
	// }
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
		pthread_mutex_init(&philo->mutex, NULL);
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
	pthread_mutex_init(&state->exit_mutex, NULL);
	// pthread_mutex_init(&state->philo->eat_count, NULL);
	pthread_mutex_lock(&state->exit_mutex);
	
	// pthread_mutex_lock(&state->philo->eat_count);
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