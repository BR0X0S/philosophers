/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:40:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/08 00:18:50 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_check_str(char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (str[o] == '0')
		o++;
	while (str[i] != '\0')
		i++;
	if (i - o > 19)
		return (-1);
	return (0);
}

long	ft_atol(char *str)
{
	t_var	data;

	data.i = 0;
	data.sign = 1;
	data.result = 0;
	if (ft_check_str(str) == -1)
		return (-1);
	if (str[data.i] == '-' || str[data.i] == '+')
		return (-1);
	while ((str[data.i] >= '0' && str[data.i] <= '9'))
	{
		data.result = data.result * 10 + (str[data.i] - '0');
		data.i++;
	}
	if (str[data.i])
		return (-1);
	data.result *= data.sign;
	if (data.result < 0)
		return (-1);
	return (data.result);
}
