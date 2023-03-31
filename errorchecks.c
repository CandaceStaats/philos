#include "philo.h"
int	errorChecks(t_env *env, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (isvalid(argc, argv))
			return (0);
		if (ft_atoi(argv[i]) == 0)
			return (0);
		i++;
	}
	env->num_of_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->philo_must_eat = ft_atoi(argv[5]);
	else
		env->philo_must_eat = 0;
	if (env->num_of_philos < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0 || env->philo_must_eat < 0)
		return (-1);
	return (0);
}
void *isvalid(int argc, char **argv)
{
    int n;

    n = 1;
    while (n < argc)
    {
        if (ft_isdigitstr(argv[n]) == -1)
        {
            printf("Not a valid input");
            exit(EXIT_FAILURE);
        }
        if (ft_atoi(argv[n]) < INT32_MIN || ft_atoi(argv[n]) > INT32_MAX)
        {
            printf("Error, Outside the bounds of integer");
            exit(EXIT_FAILURE);
        }
        n++;
    }
	return (0);
}

int ft_isdigitstr(const char *str)
{
    int i;

    i = 0;
	
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
            return (-1);
        i++;
    }
    return (0);
}