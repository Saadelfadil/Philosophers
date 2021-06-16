/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 10:58:44 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/16 16:52:49 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads_2(t_state *state)
{
	int	i;
	int	status;

	i = 0;
	while (i < state->num_of_philo)
	{
		state->philo->id = i + 1;
		state->pid[i] = fork();
		if (state->pid[i] == 0)
			myfunc((void *)state->philo);
		else
			i++;
		usleep(800);
	}
	i = 0;
	while (i < state->num_of_philo)
	{
		waitpid((pid_t) - 1, &status, 0);
		if (WIFEXITED(status) == 1)
			break ;
		i += 1;
	}
	i = 0;
	while (i < state->num_of_philo)
		kill(state->pid[i++], SIGKILL);
}

int	start_threads_1(t_state *state)
{
	pthread_t	t_eat_count;

	state->pid = malloc(sizeof(pid_t) * state->num_of_philo);
	state->start = get_time_stamp();
	if (state->notepme != -1)
		pthread_create(&t_eat_count, NULL, &eat_counter, (void *)state);
	start_threads_2(state);
	free(state->pid);
	free(state->philo);
	exit(0);
}

t_philo	*init_philo(t_state *state)
{
	t_philo	*philo;
	int		i;

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
		i++;
	}
	philo[0].eat_count = sem_open("eat_count", O_CREAT | O_EXCL, 0666, 0);
	return (philo);
}

int	init_state(t_state *state, char **argv, int argc)
{
	int	i;

	i = 0;
	state->num_of_philo = (int)ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		state->notepme = -1;
	else if (argc == 6)
		state->notepme = ft_atoi(argv[5]);
	ft_show_error(state, argc);
	sem_unlink("mutex");
	sem_unlink("write_mutex");
	sem_unlink("exit_mutex");
	state->forks_mutex = sem_open("mutex", O_CREAT | O_EXCL, 0666, \
	state->num_of_philo);
	state->write_mutex = sem_open("write_mutex", O_CREAT | O_EXCL, 0666, 1);
	state->exit_mutex = sem_open("exit_mutex", O_CREAT | O_EXCL, 0666, 0);
	state->philo = init_philo(state);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_state	state;

	if (argc < 5 || argc > 6)
		return (arguments_error());
	else
		init_state(&state, argv, argc);
	if (start_threads_1(&state))
		return (exit_error("error: in threads\n"));
	return (0);
}
