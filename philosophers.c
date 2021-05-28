/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 19:46:56 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int		init_philo(s_philo *philo, char **argv, int argc)
{
	if ((philo->num_of_philo = (int) ft_atoi(argv[1])) == 0)
		return arguments_error();
	if ((philo->time_to_die = ft_atoi(argv[2])) == 0)
		return arguments_error();
	if ((philo->time_to_eat = ft_atoi(argv[3])) == 0)
		return arguments_error();
	if ((philo->time_to_sleep = ft_atoi(argv[4])) == 0)
		return arguments_error();
	if (argc == 5)
		philo->notepme = -1;
	else
		if ((philo->notepme = ft_atoi(argv[5])) == 0)
			return arguments_error();
	return (0);
}

int		start_threads(s_philo *philo)
{
	printf("Hey philos : %d\n", philo->num_of_philo);
	return (0);
}

int	main(int argc, char *argv[])
{
	s_philo philo;
	if (argc < 5 || argc > 6)
		return arguments_error();
	else
		init_philo(&philo, argv, argc);
	if (start_threads(&philo))
		return (exit_error("error: fatal\n"));
	// printf("1 : %d\n", philo.num_of_philo);
	// printf("2 : %ld\n", philo.time_to_die);
	// printf("3 : %ld\n", philo.time_to_eat);
	// printf("4 : %ld\n", philo.time_to_sleep);
	// printf("5 : %ld\n", philo.notepme);
	return (0);
}