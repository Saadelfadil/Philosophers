/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:05:18 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/29 19:39:04 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

typedef struct s_state
{
    int num_of_philo;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long notepme;

    pthread_mutex_t write_mutex;
    pthread_mutex_t *forks_mutex;
    struct s_philo *philo;

} t_state;

typedef struct s_philo
{
    int id;
    int lfork;
    int rfork;
    int last_time_eat;

    struct s_state *state;
} t_philo;

long ft_atoi(const char *str);
int arguments_error();
int ft_strlen(char const *str);
int exit_error(char const *str);
void ft_putnbr_fd(int n, int fd);

#endif