/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 10:08:12 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:13:59 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	res;
	int	cnt;
	int	pos;

	res = 0;
	cnt = 0;
	pos = 1;
	while (str[cnt] == '\n' || str[cnt] == ' ' || str[cnt] == '\t'
		|| str[cnt] == '\v' || str[cnt] == '\f' || str[cnt] == '\r')
		cnt++;
	if (str[cnt] == '-')
	{
		pos = -1;
		cnt++;
	}
	else if (str[cnt] == '+')
		cnt++;
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		res = res * 10 + str[cnt] - '0';
		cnt++;
	}
	return (res * pos);
}

unsigned long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long)(tv.tv_sec * 1000) +
		(unsigned long long)(tv.tv_usec / 1000));
}

size_t	ft_strlen(char const *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt] != 0)
	{
		cnt++;
	}
	return (cnt);
}

int	check_must_eat(t_env *env)
{
	int	steve;

	steve = 0;
	pthread_mutex_lock(&env->must_eat_lock);
	if (env->must_eat == 1)
		steve = 1;
	pthread_mutex_unlock(&env->must_eat_lock);
	return (steve);
}

int	check_times_eaten(t_philo *philo)
{
	int	times_eaten;

	pthread_mutex_lock(&philo->times_eaten_lock);
	times_eaten = philo->times_eaten;
	pthread_mutex_unlock(&philo->times_eaten_lock);
	return (times_eaten);
}
