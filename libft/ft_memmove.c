/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 07:24:44 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/15 11:31:09 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t size)
{
	const char	*sourc;
	char		*dest;
	size_t		i;

	sourc = (const char *)src;
	dest = (char *)dst;
	i = 0;
	if ((src == dst) || size == 0)
		return (dst);
	if (dest > sourc)
		while (size-- > 0)
			dest[size] = sourc[size];
	else
	{
		i = 0;
		while (i < size)
		{
			dest[i] = sourc[i];
			i++;
		}
	}
	return (dst);
}
