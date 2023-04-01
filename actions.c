#include "philo.h"



void	print(char *message, t_philo *philo, int unlock)
{
	char	*timedMessage;

	timedMessage = ft_itoa(get_time_in_ms() - philo->env->start);
	pthread_mutex_lock(&philo->env->wrt);
	if (checkStop(philo->env) == 0 && checkMustEat(philo->env) == 0)
		printf("%s %s %s\n", timedMessage, philo->pos_str, message);
	if (unlock)
		pthread_mutex_unlock(&philo->env->wrt);
	free(timedMessage);
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
	pthread_mutex_lock(&philo->timesEatenLock);
	philo->timesEaten++;
	pthread_mutex_unlock(&philo->timesEatenLock);
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
		if (checkStop(env))
			break ;
		i = 0;
		while (env->philo_must_eat && i < env->num_of_philos
			&& checkTimesEaten(&philo[i]) >= env->philo_must_eat)
			i++;
		pthread_mutex_lock(&env->must_eat_lock);
		env->must_eat = (i == env->num_of_philos);
		pthread_mutex_unlock(&env->must_eat_lock);
	}
}