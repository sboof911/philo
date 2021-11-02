/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:23:50 by amaach            #+#    #+#             */
/*   Updated: 2021/11/02 17:09:39 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_philosophers
{
	pthread_t			thread;
	unsigned long long	last_eat;
	unsigned long long	nb_meals;
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
	pthread_mutex_t		*forks;
}				t_infos;

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

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_is_alldigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *s)
{
	int		x;
	int		t;

	x = 0;
	t = 1;
	if (!*s)
		return (0);
	while (*s == ' ' || *s <= '\n' || *s == '\v' || *s == '\r'
		|| *s == '\t' || *s == '\f')
		s++;
	if (*s == '-')
		t *= -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9' && *s)
	{
		if (t > 0 && x < 0)
			return (-1);
		if (t < 0 && x < 0)
			return (0);
		x = (x * 10) + *s - '0';
		s++;
	}
	return (x * t);
}

int	initialisation(char **argv, int argc)
{
	t_infos		*info;

	info = statlist();
	if (ft_is_alldigit(argv[1]) && ft_is_alldigit(argv[2])
		&& ft_is_alldigit(argv[3]) && ft_is_alldigit(argv[4]))
	{
		info->number = ft_atoi(argv[1]);
		info->die = ft_atoi(argv[2]);
		info->eat = ft_atoi(argv[3]);
		info->sleep = ft_atoi(argv[4]);
		if (argc == 6)
		{
			if (ft_is_alldigit(argv[5]))
				info->pme = ft_atoi(argv[5]);
			else
				return (1);
		}
		else
			info->pme = -22;
	}
	else
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	int		id;
	t_infos	*info;

	id = *(int *)arg;
	info = statlist();
	info->philo[id].nb_meals = 0;
	while (1)
	{
		pthread_mutex_lock(&info->forks[id]);
		printf("%lld %d has taken a fork\n", ft_gettime(), id);
		pthread_mutex_lock(&info->forks[(id + 1) % info->number]);
		printf("%lld %d has taken a fork\n", ft_gettime(), id);
		info->philo[id].last_eat = ft_gettime();
		info->philo[id].nb_meals++;
		printf("%lld %d is eating\n", ft_gettime(), id);
		my_sleep(info->eat);
		pthread_mutex_unlock(&info->forks[id]);
		pthread_mutex_unlock(&info->forks[(id + 1) % info->number]);
		printf("%lld %d is sleeping\n", ft_gettime(), id);
		my_sleep(info->sleep);
		printf("%lld %d is thinking\n", ft_gettime(), id);
	}
	return (0);
}

int	check_death(void)
{
	t_infos				*info;
	unsigned long long	test;
	int					full;
	int					i;

	full = 0;
	i = 0;
	info = statlist();
	while (i < info->number)
	{
		test = ft_gettime() - info->philo[i].last_eat;
		if (info->die <= (ft_gettime() - info->philo[i].last_eat))
		{
			printf("%lld %d died\n", ft_gettime(), i);
			return (1);
		}
		if (info->pme >= 0)
			full += (info->philo[i].nb_meals >= info->pme);
		if (full == info->number)
			return (1);
		i++;
	}
	return (0);
}

int	beggin(int i)
{
	int		*id;
	t_infos	*info;

	info = statlist();
	while (i < info->number)
		pthread_mutex_init(&info->forks[i++], NULL);
	i = 0;
	id = malloc(sizeof (int));
	while (i < info->number)
	{
		*id = i;
		info->philo[i].last_eat = ft_gettime();
		pthread_create(&info->philo[i].thread, NULL, &routine, id);
		usleep(100);
		i++;
	}
	while (1)
	{
		if (check_death())
			return (1);
	}
	i = 0;
	while (i < info->number)
		pthread_join(info->philo[i++].thread, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_infos		*info;
	int			i;

	i = 0;
	info = statlist();
	if (argc == 5 || argc == 6)
	{
		if (initialisation(argv, argc))
			return (1);
		info->philo = malloc((sizeof (t_philosophers)) * info->number);
		info->forks = malloc((sizeof (pthread_mutex_t)) * info->number);
		if (beggin(0))
			return (1);
	}
	else
		printf("Number of args is unavailable\n");
}
// TODO : for forks he can take his and his + 1 % (number_of_philo)