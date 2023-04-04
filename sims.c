/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sims.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 09:57:33 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:48:14 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*simulation(void *params)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)params;
	env = philo->env;
	if (philo->pos % 2 == 0 && env->num_of_philos > 1)
		sleepy(env->time_to_eat / 50, env);
	while (check_stop(env) == 0 && check_must_eat(env) == 0)
	{
		eat(philo);
		print("is sleeping", philo, UNLOCK);
		sleepy(env->time_to_sleep, env);
		print("is thinking", philo, UNLOCK);
	}
	return (NULL);
}

static void	exit_threads(t_env *env)
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

int	start_threads(t_env *env)
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
	exit_threads(env);
	return (1);
}

void	sleepy(unsigned long long timing, t_env *env)
{
	unsigned long	begin;

	begin = get_time_in_ms();
	while (check_stop(env) == 0)
	{
		if (get_time_in_ms() - begin >= timing)
			break ;
		usleep(300);
	}
}

char	*ft_strdup(const char *s1)
{
	char	*cpy_s1;
	size_t	cnt;

	cnt = 0;
	cpy_s1 = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (cpy_s1 == NULL)
		return (NULL);
	while (s1[cnt] != '\0')
	{
		cpy_s1[cnt] = s1[cnt];
		cnt++;
	}
	cpy_s1[cnt] = '\0';
	return (cpy_s1);
}
