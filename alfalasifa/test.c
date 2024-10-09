/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:56:33 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/09 18:29:08 by oumondad         ###   ########.fr       */
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

void	*rotine(void *args)
{
	t_var *data = (t_var *)args;
		pthread_mutex_lock(&data->lock);
		data->start = get_time();
		pthread_mutex_unlock(&data->lock);
	while (data->i < 10)
	{
		sleep(1);
		pthread_mutex_lock(&data->lock);
		data->i++;
		pthread_mutex_unlock(&data->lock);
	}
}

void	*rotine2(void *args)
{
	t_var *data = (t_var *)args;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		if (get_time() - data->start >= 3000)
		{
			printf("i = %ld\n", data->i);
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

int	main(void)
{
	long			time;
	long			time2;
	pthread_t		thrd1;
	pthread_t		thrd2;
	struct timeval	tv;
	t_var			data;

	data.i = 0;
	pthread_mutex_init(&data.lock, NULL);
	pthread_create(&thrd1, NULL, rotine, &data);
	pthread_create(&thrd2, NULL, rotine2, &data);
	pthread_join(thrd1, NULL);
	pthread_join(thrd2, NULL);
	// printf("i = %ld\n", data.i);
	return (0);
}
