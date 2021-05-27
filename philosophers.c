/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/27 14:45:52 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

void	init_philo(s_philo *philo, char **argv)
{
	philo->num_of_philo = *argv[1];
	philo->time_to_die = *argv[2];
	philo->time_to_eat = *argv[3];
	philo->time_to_sleep = *argv[4];
	philo->notepme = *argv[5];
	printf("Heyy : %ld\n", philo->time_to_eat);
}

int	main(int argc, char *argv[])
{
	s_philo philo;
	init_philo(&philo, argv);
	return (0);
}