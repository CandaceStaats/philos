#include "philo.h"
int	main(int argc, char *argv[])
{
	t_env	env;

	env.must_eat = 0;
	env.stop = 0;
	if (argc < 5 || argc > 6)
		return (printf("Incorrect Amount of parameters"));
	if (errorChecks(&env, argc, argv) == -1)
		return (printf("Incorrect Parameters Given.\n"));
	if (!startSim(&env))
		return (printf("Error in Initialization.\n"));
	if (!startThreads(&env))
		return (printf("Error in Actions.\n"));
	return (0);
}
