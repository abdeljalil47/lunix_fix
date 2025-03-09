/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:00:00 by abdsebba          #+#    #+#             */
/*   Updated: 2024/10/30 14:34:20 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scanstr(char str, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == str)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	j = len;
	while (s1[i])
	{
		if (ft_scanstr(s1[i], set))
			i++;
		else
			break ;
	}
	while (j > i)
	{
		if (ft_scanstr(s1[j - 1], set))
			j--;
		else
			break ;
	}
	return (ft_substr(s1, i, (j - i)));
}
