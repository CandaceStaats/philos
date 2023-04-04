/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 09:58:42 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:40:07 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define UNLOCK 1
# define LOCK 0

struct	s_env;

typedef struct s_philo
{
	int				times_eaten;
	int				left_fork;
	int				right_fork;
	int				pos;
	char			*pos_str;
	unsigned long	last_ate;
	struct s_env	*env;
	pthread_t		thread_id;
	pthread_mutex_t	times_eaten_lock;
}				t_philo;

typedef struct s_env
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	unsigned long	start;
	int				stop;
	int				must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meal;
	pthread_mutex_t	stoplock;
	pthread_mutex_t	wrt;
	pthread_mutex_t	must_eat_lock;
}				t_env;

int					isvalid(int argc, char **argv);
int					error_checks(t_env *env, int argc, char *argv[]);
int					start_sim(t_env *env);
void				print(char *msg, t_philo *philo, int unlock);
void				eat(t_philo *philo);
void				dead(t_env *env, t_philo *philo);
int					start_threads(t_env *env);
unsigned long long	get_time_in_ms(void);
void				sleepy(unsigned long long timing, t_env *env);
int					ft_atoi(char *str);
size_t				ft_strlen(char const *str);
int					ft_isdigit(int c);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nitems, size_t size);
char				*ft_itoa(int n);
int					ft_isdigitstr(const char *str);
char				*ft_strdup(const char *s1);
void				cleanup_mutexes(t_env *env);
int					check_stop(t_env *env);
int					check_must_eat(t_env *env);
int					check_times_eaten(t_philo *philo);
void				dead_while(t_env *env, t_philo *philo);

#endif
