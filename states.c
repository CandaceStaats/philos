#include "philo.h"

static int	createPhilo(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		env->philos[i].timesEaten = 0;
		env->philos[i].pos = i + 1;
		env->philos[i].pos_str = ft_itoa(i + 1);
		if (!env->philos[i].pos_str)
			break ;
		env->philos[i].left_fork = i;
		env->philos[i].right_fork = (i + 1) % env->num_of_philos;
		env->philos[i].env = env;
		if (pthread_mutex_init(&(env->philos[i].timesEatenLock), NULL))
			return (1);
		i++;
	}
	if (i != env->num_of_philos)
	{
		while (i >= 0)
		{
			free(env->philos[i].pos_str);
			i--;
		}
		return (1);
	}
	return (0);
}

static int	createForks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		i++;
	}
	return (0);
}

static int	createMutexes(t_env *env)
{
	if (pthread_mutex_init(&env->meal, NULL) ||
		pthread_mutex_init(&env->wrt, NULL) ||
		pthread_mutex_init(&env->must_eat_lock, NULL) ||
		pthread_mutex_init(&env->stoplock, NULL))
	{
		cleanup_mutexes(env);
		return (1);
	}
	return (0);
}

int	startSim(t_env *env)
{
	env->philos = malloc(sizeof(t_philo) * env->num_of_philos);
	if (!env->philos)
		return (EXIT_FAILURE);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_of_philos);
	if (!env->forks)
	{
		free(env->philos);
		return (EXIT_FAILURE);
	}
	if (createForks(env) || createMutexes(env))	{
		free(env->philos);
		free(env->forks);
		return (EXIT_FAILURE);
	}
	if (createPhilo(env))
	{
		free(env->philos);
		free(env->forks);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	cleanup_mutexes(t_env *env)
{
	int i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_destroy(&(env->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&env->meal);
	pthread_mutex_destroy(&env->wrt);
	pthread_mutex_destroy(&env->must_eat_lock);
	pthread_mutex_destroy(&env->stoplock);
}