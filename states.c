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

static int	createMutex(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&env->meal, NULL))
		return (1);
	if (pthread_mutex_init(&env->writing, NULL))
		return (1);
	return (0);
}

int	startSim(t_env *env)
{
	env->philos = malloc(sizeof(t_philo) * env->num_of_philos);
	if (!env->philos)
		return (0);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->num_of_philos);
	if (!env->forks)
	{
		free(env->philos);
		return (0);
	}
	if (createMutex(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	if (createPhilo(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	return (1);
}