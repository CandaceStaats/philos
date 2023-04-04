/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   contutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cstaats <cstaats@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 10:39:21 by cstaats       #+#    #+#                 */
/*   Updated: 2023/04/04 10:39:30 by cstaats       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*pnt;

	pnt = malloc(nitems * size);
	if (pnt == NULL)
		return (NULL);
	ft_bzero(pnt, (nitems * size));
	return (pnt);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cnt;

	cnt = (unsigned char *)s;
	while (n)
	{
		n--;
		*cnt = 0;
		cnt++;
	}
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	ft_mem(long int store)
{
	int	len;

	len = 0;
	if (store == 0)
		len = 1;
	else if (store < 0)
	{
		len = 1;
		store = -store;
	}
	while (store)
	{
		store /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == INT32_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_mem(n);
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 9)
	{
		str[len - 1] = n % 10 + '0';
		n /= 10;
		len--;
	}
	str[len - 1] = n % 10 + '0';
	return (str);
}
