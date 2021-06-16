/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-fadi <sel-fadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:23:58 by sel-fadi          #+#    #+#             */
/*   Updated: 2021/06/15 19:05:04 by sel-fadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	arguments_error(void)
{
	printf("error: bad arguments\n");
	return (-1);
}

int	exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
	write(fd, " ", 1);
}

void	ft_putlong_fd(long long n, int fd)
{
	char	str[19];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
	write(fd, " ", 1);
}
