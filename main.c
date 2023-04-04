/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 09:48:13 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:02:04 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error_print(char *str)
{
	printf("%s", str);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	env.must_eat = 0;
	env.stop = 0;
	if (argc < 5 || argc > 6)
		return (error_print("Incorrect Amount of parameters.\n"));
	if (error_checks(&env, argc, argv) == -1)
		return (error_print("Incorrect Parameters Given.\n"));
	if (start_sim(&env))
		return (error_print("Error in Initialization.\n"));
	if (!start_threads(&env))
		return (error_print("Error in Actions.\n"));
	return (0);
}
