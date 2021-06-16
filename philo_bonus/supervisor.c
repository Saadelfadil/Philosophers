/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:49:18 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/16 16:59:05 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*supervisor(void *philo_)
{
	t_philo	*philo;

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
			exit(1);
			sem_post(philo->state->write_mutex);
			sem_post(philo->mutex);
			sem_post(philo->state->exit_mutex);
			break ;
		}
		sem_post(philo->mutex);
	}
	return (NULL);
}

void	*eat_counter(void *state_)
{
	t_state	*state;
	t_philo	*philo;
	int		i;
	int		j;

	i = 0;
	state = (t_state *)state_;
	philo = state->philo;
	while (i < state->notepme)
	{
		j = 0;
		while (j++ < state->num_of_philo)
		{
			sem_wait(philo[0].eat_count);
			sem_wait(state->write_mutex);
			sem_post(state->write_mutex);
		}
		i++;
	}
	sem_wait(state->write_mutex);
	printf("DONE\n");
	i = 0;
	while (state->pid[i])
		kill(state->pid[i++], SIGKILL);
	exit(1);
}

void	*myfunc(t_philo *philo)
{
	pthread_t	t_id;

	philo->last_time_eat = (long)get_time_stamp();
	philo->limit = philo->last_time_eat + philo->state->time_to_die;
	philo->is_eating = 0;
	pthread_create(&t_id, NULL, &supervisor, philo);
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
