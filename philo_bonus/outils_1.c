/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:49:09 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/16 17:06:28 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

long long	get_time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_show_error(t_state *state, int argc)
{
	if (state->num_of_philo == 0)
		return (exit_error("error: bad arguments\n"));
	if (state->time_to_die == 0)
		return (exit_error("error: bad arguments\n"));
	if (state->time_to_eat == 0)
		return (exit_error("error: bad arguments\n"));
	if (state->time_to_sleep == 0)
		return (exit_error("error: bad arguments\n"));
	if (argc == 6 && state->notepme == 0)
		return (exit_error("error: bad arguments\n"));
	return (0);
}
