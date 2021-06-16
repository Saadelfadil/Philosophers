/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:06:56 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/15 19:13:45 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think_func(t_state *state, t_philo *philo)
{
	ft_logger(3, get_time_stamp(), philo->id, state);
}

void	take_forks(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_lock(&philo->state->forks_mutex[philo->lfork]);
	ft_logger(4, get_time_stamp(), philo->id, state);
}

void	drops_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->state->forks_mutex[philo->lfork]);
}

void	sleep_func(t_state *state)
{
	ft_logger(2, get_time_stamp(), state->philo->id, state->philo->state);
	ft_sleep(state->time_to_sleep);
}

void	eat_func(t_state *state, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_time_eat = (get_time_stamp());
	philo->limit = philo->last_time_eat + state->time_to_die;
	philo->is_eating = 1;
	ft_logger(1, get_time_stamp(), philo->id, state);
	pthread_mutex_unlock(&philo->mutex);
	ft_sleep(state->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat_count);
}
