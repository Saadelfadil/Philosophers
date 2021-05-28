/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:05:18 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 19:40:07 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef struct s_philo
{
    int     num_of_philo;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    notepme;
}s_philo;

long	ft_atoi(const char *str);
int     arguments_error();
int     ft_strlen(char const *str);
int     exit_error(char const *str);

# endif