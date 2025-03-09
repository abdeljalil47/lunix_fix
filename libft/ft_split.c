/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:04:25 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/14 09:56:15 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_token(const char *s, char c)
{
	size_t	token;
	int		flag;

	token = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else
		{
			if (flag)
			{
				token++;
				flag = 0;
			}
		}
		s++;
	}
	return (token);
}

static int	safe_malloc(char **strings, int position, size_t buffer)
{
	int	i;

	i = 0;
	strings[position] = malloc(buffer);
	if (strings[position] == NULL)
	{
		while (i < position)
		{
			free(strings[i]);
			i++;
		}
		free(strings);
		return (1);
	}
	return (0);
}

static int	ft_fill_strs(char **strings, const char *s, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (safe_malloc(strings, i, len + 1))
				return (1);
			ft_strlcpy(strings[i], s - len, len + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	size_t	word_count;
	char	**strings;

	if (s == NULL)
		return (NULL);
	word_count = ft_count_token(s, c);
	strings = malloc((word_count + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	strings[word_count] = NULL;
	if (ft_fill_strs(strings, s, c))
		return (NULL);
	return (strings);
}
