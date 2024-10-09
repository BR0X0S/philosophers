/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:56:33 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/09 19:09:26 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	*rotin1(void *args)
{
	t_var	*data = (t_var *)args;
	// pthread_mutex_lock(&data->lock);
	// data->start = get_time();
	// pthread_mutex_unlock(&data->lock);
	while (data->i < 10)
	{
		sleep(1);
		pthread_mutex_lock(&data->lock);
		data->i++;
		pthread_mutex_unlock(&data->lock);
	}
}

void	*rotin2(void *args)
{
	t_var	*data = (t_var *)args;
	pthread_mutex_lock(&data->lock);
	data->start = get_time();
	pthread_mutex_unlock(&data->lock);
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (get_time() - data->start >= 3000)
		{
			printf("After 3s the i = %ld\n", data->i);
			data->start = get_time();
		}
		if (data->i >= 10)
		{
			pthread_mutex_unlock(&data->lock);
			break;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(5000);
	}
}

int main(void)
{
	t_var		data;
	pthread_t	philo1;
	pthread_t	philo2;

	pthread_mutex_init(&data.lock, NULL);
	data.i = 0;
	pthread_create(&philo1, NULL, rotin1, &data);
	pthread_create(&philo2, NULL, rotin2, &data);
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);
	printf("i = %ld\n", data.i);
	pthread_mutex_destroy(&data.lock);
}
