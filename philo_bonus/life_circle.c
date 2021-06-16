/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:49:04 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/16 17:15:23 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think_func(t_state *state, t_philo *philo)
{
	sem_wait(state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " \x1B[34mis thinking\x1B[0m", \
	ft_strlen(" \x1B[34mis thinking\x1B[0m"));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
}

void	take_forks(t_state *state, t_philo *philo)
{
	sem_wait(state->forks_mutex);
	sem_wait(state->forks_mutex);
	sem_wait(state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " \x1B[35mhas taken a fork\x1B[0m", \
	ft_strlen(" \x1B[35mhas taken a fork\x1B[0m"));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
}

void	drops_forks(t_philo *philo)
{
	sem_wait(philo->state->write_mutex);
	ft_putlong_fd((get_time_stamp()), 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " \x1B[33mis sleeping\x1B[0m", \
	ft_strlen(" \x1B[33mis sleeping\x1B[0m"));
	write(1, "\n", 1);
	sem_post(philo->state->write_mutex);
	sem_post(philo->state->forks_mutex);
	sem_post(philo->state->forks_mutex);
}

void	sleep_func(t_state *state)
{
	usleep(state->time_to_sleep * 1000);
}

void	eat_func(t_state *state, t_philo *philo)
{
	sem_wait(philo->mutex);
	sem_wait(state->write_mutex);
	philo->last_time_eat = (get_time_stamp());
	philo->limit = philo->last_time_eat + state->time_to_die;
	philo->is_eating = 1;
	ft_putlong_fd(philo->last_time_eat, 1);
	ft_putnbr_fd(philo->id, 1);
	write(1, " \x1B[32mis eating\x1B[0m", \
	ft_strlen(" \x1B[32mis eating\x1B[0m"));
	write(1, "\n", 1);
	sem_post(state->write_mutex);
	sem_post(philo->mutex);
	usleep(state->time_to_eat * 1000);
	philo->is_eating = 0;
	sem_post(philo->eat_count);
}
