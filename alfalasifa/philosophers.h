/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:06 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/08 19:06:48 by oumondad         ###   ########.fr       */
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
	long			i;
	long			start;
	long			end;
	long			total_time;
	long			nop;
	long			ttd;
	long			tte;
	long			tts;
	long			nom;
	long			time;
	pthread_mutex_t	lock;
}	t_var;

long	ft_atol(char *str);
long	get_time(void);

#endif