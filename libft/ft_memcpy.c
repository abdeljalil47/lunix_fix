/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:26:16 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/15 10:03:40 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	const char	*sourc;
	char		*dest;
	size_t		i;

	sourc = (const char *)src;
	dest = (char *)dst;
	i = 0;
	if (sourc == dest)
		return (dest);
	while (i < size)
	{
		dest[i] = sourc[i];
		i++;
	}
	return (dst);
}
