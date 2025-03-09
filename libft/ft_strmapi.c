/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:33:51 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/15 14:07:31 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*place;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	place = (char *)malloc((len + 1) * sizeof(char));
	if (place == NULL)
		return (NULL);
	while (i < len)
	{
		place[i] = f((unsigned int)i, s[i]);
		i++;
	}
	place[i] = '\0';
	return (place);
}
