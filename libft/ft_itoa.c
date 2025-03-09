/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:03:34 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/12 14:55:40 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_count_itoa(long long n)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_fill_buffer(long long n, char *buffer, long long i)
{
	if (n == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return (buffer);
	}
	if (n < 0)
	{
		buffer[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (buffer);
}

char	*ft_itoa(int nb)
{
	char		*buffer;
	long long	n;
	int			len;
	long long	i;

	n = nb;
	len = ft_count_itoa(n);
	i = len - 1;
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	ft_fill_buffer(n, buffer, i);
	buffer[len] = '\0';
	return (buffer);
}
