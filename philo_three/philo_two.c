/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/09 15:07:48 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long get_time_stamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void think_func(t_state *state, t_philo *philo)
{
	sem_wait(state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "THINKING   ", ft_strlen("THINKING   "));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
}

void take_forks(t_state *state, t_philo *philo)
{
	sem_wait(state->forks_mutex);
	sem_wait(state->forks_mutex);
	sem_wait(state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "Take forks", ft_strlen("Take forks"));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
}

void drops_forks(t_philo *philo)
{
	sem_wait(philo->state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is sleeping ", ft_strlen("philosopher is sleeping "));
	write(1, "\n", 1);
	sem_post(philo->state->write_mutex);
	sem_post(philo->state->forks_mutex);
	sem_post(philo->state->forks_mutex);
}

void sleep_func(t_state *state)
{
	usleep(state->time_to_sleep * 1000);
}

void eat_func(t_state *state, t_philo *philo)
{
	sem_wait(philo->mutex);
	sem_wait(state->write_mutex);
	philo->last_time_eat = (get_time_stamp());
	philo->limit = philo->last_time_eat + state->time_to_die;
	philo->is_eating = 1;
	ft_putlong_fd(philo->last_time_eat, 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, "philosopher is eating ", ft_strlen("philosopher is eating "));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
	sem_post(philo->mutex);
	usleep(state->time_to_eat * 1000);
	philo->is_eating = 0;
	sem_post(philo->eat_count);
}

void *supervisor(void *philo_)
{
	t_philo *philo;

	philo = (t_philo *)philo_;
	while (1)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time_stamp() > philo->limit)
		{
			sem_wait(philo->state->write_mutex);
			ft_putlong_fd((get_time_stamp()), 1);
			ft_putnbr_fd(philo->id, 1);
			write(1, "philosopher is died", ft_strlen("philosopher is died"));
			write(1, "\n", 1);
			sem_post(philo->state->write_mutex);
			sem_post(philo->mutex);
			sem_post(philo->state->exit_mutex);
			break;
		}
		sem_post(philo->mutex);
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
			sem_wait(philo[j].eat_count);
			j++;
		}
		i++;
	}
	sem_wait(state->write_mutex);
	printf("DONE\n");
	sem_post(state->exit_mutex);
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
	pthread_create(&t_id, NULL, &supervisor, philo_);
	while (1)
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
	sem_wait(state->exit_mutex);
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
	sem_unlink("mutex");
	sem_unlink("eat_count");
	while (i < state->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].rfork = ((i + 1) + 1) % state->num_of_philo;
		philo[i].lfork = i + 1;
		philo[i].state = state;
		philo[i].last_time_eat = (int)(get_time_stamp());
		philo[i].mutex = sem_open("mutex", O_CREAT | O_EXCL, 0666, 1);
		philo[i].eat_count = sem_open("eat_count", O_CREAT | O_EXCL, 0666, 1);
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
	sem_unlink("mutex");
	sem_unlink("write_mutex");
	sem_unlink("exit_mutex");
	state->forks_mutex = sem_open("mutex", O_CREAT | O_EXCL, 0666, state->num_of_philo);
	state->write_mutex = sem_open("write_mutex", O_CREAT | O_EXCL, 0666, 1);
	state->exit_mutex = sem_open("exit_mutex", O_CREAT | O_EXCL, 0666, 0);
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