/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:54:42 by amaach            #+#    #+#             */
/*   Updated: 2021/11/05 12:02:25 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_gettime(void)
{
	struct timeval		time;
	unsigned long long	time_in_mill;

	gettimeofday(&time, NULL);
	time_in_mill = (time.tv_sec) * 1000 + (time.tv_usec) / 1000;
	return (time_in_mill);
}

t_infos	*statlist(void)
{
	static t_infos	ret;

	return (&ret);
}

void	my_sleep(unsigned long long i)
{
	unsigned long long	current_time;
	unsigned long long	time_beggin;

	time_beggin = ft_gettime();
	while (1)
	{
		usleep(100);
		current_time = ft_gettime();
		if (current_time >= time_beggin + i)
			break ;
	}
}
