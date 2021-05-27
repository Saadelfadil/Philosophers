/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:05:18 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/27 12:20:18 by sel-fadi         ###   ########.fr       */
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

# endif