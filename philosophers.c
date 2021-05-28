/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 16:05:29 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

long		ft_atoi(const char *str)
{
	int			i;
	long		ope;
	long		resu;

	i = 0;
	while ((str[i] > 0 && str[i] < 27) || (str[i] > 27 && str[i] <= 32))
		i++;
	ope = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ope = -1;
		i++;
	}
	resu = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (resu < 0 && ope < 0)
			return (0);
		if (resu < 0 && ope > 0)
			return (-1);
		resu = resu * 10 + (str[i] - '0');
		i++;
	}
	return (resu * ope);
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	arguments_error()
{
	printf("Argument Error\n");
}

void	init_philo(s_philo *philo, char **argv, int argc)
{
	philo->num_of_philo = (int) ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		philo->notepme = -1;
	else
		philo->notepme = ft_atoi(argv[5]);
	// printf("Hello : %ld\n", philo->time_to_sleep);
}

int	main(int argc, char *argv[])
{
	s_philo philo;
	if (argc == 5 || argc == 6)
		init_philo(&philo, argv, argc);
	else
		arguments_error();
	printf("1 : %d\n", philo.num_of_philo);
	printf("2 : %ld\n", philo.time_to_die);
	printf("3 : %ld\n", philo.time_to_eat);
	printf("4 : %ld\n", philo.time_to_sleep);
	printf("5 : %ld\n", philo.notepme);
	return (0);
}