/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:01:20 by ggneme            #+#    #+#             */
/*   Updated: 2022/11/05 23:05:22 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_strlcpy_mod(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	if (size > 0)
	{
		while (src[n] != '\0' && n < size - 1)
		{
			dest[n] = src[n];
			n ++;
		}
		dest[n] = '\0';
	}
	return (0);
}

static size_t	ft_strlcat_mod(char *dest, const char *src, size_t size)
{
	size_t	n;
	size_t	i;
	size_t	len;

	if (size == 0 && !dest)
		return (ft_strlen(src));
	i = ft_strlen(dest);
	len = i;
	n = 0;
	if (size <= i)
		return (size + ft_strlen(src));
	while (src[n] != '\0' && i < size - 1)
		dest[i++] = src[n++];
	dest[i] = '\0';
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*string;
	size_t		s1_len;
	size_t		s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (string)
	{
		ft_strlcpy_mod(string, s1, s1_len + 1);
		ft_strlcat_mod(string, s2, s1_len + s2_len + 1);
	}
	return (string);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s1);
	dest = malloc((len + 1) * sizeof(char));
	if (dest)
		ft_strlcpy_mod(dest, s1, len + 1);
	return (dest);
}
