/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:23:58 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/05/28 19:39:27 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosophers.h"

long	ft_atoi(const char *str)
{
    int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] != '\0') && (str[i] <= '9' && str[i] >= '0'))
	{
		res = ((res * 10) + (str[i] - 48));
		if (res > 2147483648 && sign == -1)
			return (0);
		else if (res > 2147483647 && sign == 1)
			return (-1);
		i++;
	}
	return (res * sign);
}

int     arguments_error()
{
	printf("error: bad arguments\n");
	return (-1);
}

int     exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int     ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}