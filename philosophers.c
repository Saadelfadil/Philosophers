/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 21:09:41 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

int saad = 0;

pthread_mutex_t mutex;

void    *myfunc(void *argv)
{
    int i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        saad++;
        i++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void    *myfunction(void *argv)
{
    static int i;
    i += 1;
    printf("Hello from thread : %d\n", i);
    return NULL;
}

int		start_threads(s_philo *philo)
{
	pthread_t t[philo->num_of_philo];
    int i = 0;

    pthread_mutex_init(&mutex, NULL);
    while (i < philo->num_of_philo)
    {
        pthread_create(&t[i], NULL, &myfunc, NULL);
        i++;
    }
    i = 0;
    while (i < philo->num_of_philo)
    {
        pthread_join(t[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&mutex);
	printf("saad : %d\n", saad);
	return (0);
}

int		init_philo(s_philo *philo, char **argv, int argc)
{
	if ((philo->num_of_philo = (int) ft_atoi(argv[1])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((philo->time_to_die = ft_atoi(argv[2])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((philo->time_to_eat = ft_atoi(argv[3])) == 0)
		return (exit_error("error: bad arguments\n"));
	if ((philo->time_to_sleep = ft_atoi(argv[4])) == 0)
		return (exit_error("error: bad arguments\n"));
	if (argc == 5)
		philo->notepme = -1;
	else
		if ((philo->notepme = ft_atoi(argv[5])) == 0)
			return (exit_error("error: bad arguments\n"));
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
		return (exit_error("error: in threads\n"));
	return (0);
}