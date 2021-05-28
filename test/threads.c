/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:39:52 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 20:49:19 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"



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