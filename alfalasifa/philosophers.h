/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:06 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/10 18:48:49 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_var
{
	t_desk			*first_filo;
	long			total_time;
	long			start;
	long			end;
	long			nop;
	long			ttd;
	long			tte;
	long			tts;
	long			nom;
	long			i;
	pthread_mutex_t	lock;
}	t_var;

typedef struct s_desk
{
	pthread_mutex_t	fork;
	pthread_t		philo;
	t_var			*data;
	long			ttd;
	long			tte;
	long			tts;
	struct s_desk	*next;
}	t_desk;

long	ft_atol(char *str);
long	get_time(void);

#endif