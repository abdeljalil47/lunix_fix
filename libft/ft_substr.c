/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:13:01 by abdsebba          #+#    #+#             */
/*   Updated: 2025/03/04 00:30:38 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cpy(const char *s, unsigned int start, char	*array, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			array[j] = s[i];
			j++;
		}
		i++;
	}
	array[j] = '\0';
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*array;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
	{
		array = (char *)malloc(sizeof(char));
		if (array != NULL)
			array[0] = '\0';
		return (array);
	}
	array = (char *)malloc((len + 1) * sizeof(char));
	if (array == NULL)
		return (NULL);
	ft_cpy(s, start, array, len);
	return (array);
}
