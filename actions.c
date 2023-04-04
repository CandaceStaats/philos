/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 10:14:42 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:43:16 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *message, t_philo *philo, int unlock)
{
	char	*timed_message;

	timed_message = ft_itoa(get_time_in_ms() - philo->env->start);
	pthread_mutex_lock(&philo->env->wrt);
	if (check_stop(philo->env) == 0 && check_must_eat(philo->env) == 0)
		printf("%s %s %s\n", timed_message, philo->pos_str, message);
	if (unlock)
		pthread_mutex_unlock(&philo->env->wrt);
	free(timed_message);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->left_fork]);
	print("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->env->forks[philo->right_fork]);
	print("has taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->env->meal);
	print("is eating", philo, UNLOCK);
	philo->last_ate = get_time_in_ms();
	pthread_mutex_unlock(&philo->env->meal);
	sleepy(philo->env->time_to_eat, philo->env);
	pthread_mutex_lock(&philo->times_eaten_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_lock);
	pthread_mutex_unlock(&philo->env->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->env->forks[philo->left_fork]);
}

void	dead(t_env *env, t_philo *philo)
{
	int	i;

	while (!env->must_eat)
	{
		i = -1;
		while (++i < env->num_of_philos && !env->stop)
		{
			pthread_mutex_lock(&env->meal);
			if ((int)(get_time_in_ms() - philo[i].last_ate) >= env->time_to_die)
			{
				print("died", &philo[i], UNLOCK);
				pthread_mutex_lock(&env->stoplock);
				env->stop = 1;
				pthread_mutex_unlock(&env->stoplock);
			}
			pthread_mutex_unlock(&env->meal);
		}
		if (check_stop(env))
			break ;
	i = 0;
		while (env->philo_must_eat && i < env->num_of_philos
			&& check_times_eaten(&philo[i]) >= env->philo_must_eat)
			i++;
		pthread_mutex_lock(&env->must_eat_lock);
		env->must_eat = (i == env->num_of_philos);
		pthread_mutex_unlock(&env->must_eat_lock);
	}
}

int	check_stop(t_env *env)
{
	int	steve;

	steve = 0;
	pthread_mutex_lock(&env->stoplock);
	if (env->stop == 1)
		steve = 1;
	pthread_mutex_unlock(&env->stoplock);
	return (steve);
}

// void	dead_while(t_env *env, t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (env->philo_must_eat && i < env->num_of_philos
// 		&& check_times_eaten(&philo[i]) >= env->philo_must_eat)
// 		i++;
// }
