/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:10:54 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/15 19:13:32 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*supervisor(void *philo_)
{
	t_philo	*philo;

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

void	*eat_counter(void *state_)
{
	t_state	*state;
	t_philo	*philo;
	int		i;
	int		j;

	i = 0;
	state = (t_state *)state_;
	philo = state->philo;
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

void	*myfunc(void *philo_)
{
	t_philo		*philo;
	pthread_t	t_id;

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
