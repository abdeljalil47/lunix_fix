/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 09:08:45 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/14 09:54:11 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	y;

	i = 0;
	j = 0;
	y = ft_strlen(src);
	if (!dst && size == 0)
		return (y);
	while (dst[j] != '\0')
	{
		j++;
	}
	x = j;
	if (size == 0 || size <= x)
		return (y + size);
	while (src [i] != '\0' && i < size - x - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (x + y);
}
