/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:56:04 by amaach            #+#    #+#             */
/*   Updated: 2021/11/05 12:02:08 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosophers
{
	pthread_t			thread;
	unsigned long long	last_eat;
	unsigned long long	nb_meals;
	int					eating;
}				t_philosophers;

typedef struct s_infos
{
	int					id;
	unsigned long long	number;
	unsigned long long	die;
	unsigned long long	eat;
	unsigned long long	sleep;
	unsigned long long	pme;
	t_philosophers		*philo;
	pthread_mutex_t		*is_eating;
	pthread_mutex_t		*forks;
	pthread_mutex_t		prints;
}				t_infos;

int					ft_isdigit(int c);
int					ft_is_alldigit(char *str);
int					ft_atoi(const char *s);
unsigned long long	ft_gettime(void);
t_infos				*statlist(void);
void				my_sleep(unsigned long long i);
t_infos				*eating(t_infos *info, int id);
void				*routine(void *arg);
int					initialisation(char **argv, int argc);
int					check_death(void);
int					beggin(unsigned long long i, int *id);
void				free_shit(t_infos *info, int *id);
#endif