#include "philo.h"
static void	*simulation(void *params)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)params;
	env = philo->env;
	if (philo->pos % 2 && env->num_of_philos > 1)
		sleepy(env->time_to_eat / 50, env);
	while (checkStop(env) == 0 && checkMustEat(env) == 0)
	{
		eat(philo);
		print("is sleeping", philo, UNLOCK);
		sleepy(env->time_to_sleep, env);
		print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}

static void	exitThreads(t_env *env)
{
	int	i;

	if (env->num_of_philos == 1)
		pthread_detach(env->philos[0].thread_id);
	else
	{
		i = -1;
		while (++i < env->num_of_philos)
			pthread_join(env->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < env->num_of_philos)
		pthread_mutex_destroy(&env->forks[i]);
	cleanup_mutexes(env);
	i = -1;
	while (++i < env->num_of_philos)
		free(env->philos[i].pos_str);
	free(env->philos);
	free(env->forks);
}


int	startThreads(t_env *env)
{
	int	i;

	i = -1;
	env->start = get_time_in_ms();
	while (++i < env->num_of_philos)
	{
		env->philos[i].last_ate = get_time_in_ms();
		if (pthread_create(&env->philos[i].thread_id,
				NULL, simulation, &(env->philos[i])))
			return (0);
	}
	dead(env, env->philos);
	exitThreads(env);
	return (1);
}

