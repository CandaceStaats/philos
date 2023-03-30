#include "philo.h"

int	ft_atoi(char *str)
{
	int	res;
	int	cnt;
	int	pos;

	res = 0;
	cnt = 0;
	pos = 1;
	while (str[cnt] == '\n' || str[cnt] == ' ' || str[cnt] == '\t'
		|| str[cnt] == '\v' || str[cnt] == '\f' || str[cnt] == '\r')
		cnt++;
	if (str[cnt] == '-')
	{
		pos = -1;
		cnt++;
	}
	else if (str[cnt] == '+')
		cnt++;
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		res = res * 10 + str[cnt] - '0';
		cnt++;
	}
	return (res * pos);
}

unsigned long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long)(tv.tv_sec * 1000) +
		(unsigned long long)(tv.tv_usec / 1000));
}

size_t	ft_strlen(char const *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt] != 0)
	{
		cnt++;
	}
	return (cnt);
}

void	sleepy(unsigned long long timing, t_env *env)
{
	unsigned long	begin;

	begin = get_time_in_ms();
	while (!env->stop)
	{
		if (get_time_in_ms() - begin >= timing)
			break ;
		usleep(env->num_of_philos * 2);
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
