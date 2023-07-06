/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:09:59 by ggneme            #+#    #+#             */
/*   Updated: 2022/11/08 15:46:20 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_end_line(char *buf, char **address)
{
	size_t	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			*address = &buf[i + 1];
			return (1);
		}
		i ++;
	}
	return (0);
}

static void	ft_traitements(char **buf, char **result, char **s1)
{
	char	c;
	char	*string;

	if (buf)
		string = ft_strjoin(*s1, *buf);
	else
		string = ft_strdup(*s1);
	free(*s1);
	if (ft_end_line(string, &(*s1)))
	{
		c = **s1;
		**s1 = '\0';
		*result = ft_strdup(string);
		**s1 = c;
		*s1 = ft_strdup(*s1);
		free(string);
	}
	else
	{
		*s1 = ft_strdup(string);
		free(string);
	}
}

static int	my_read(int fd, char **buf, char **result, char **s1)
{
	int		nbr;

	*buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (*buf)
	{
		while (1)
		{
			nbr = read(fd, *buf, BUFFER_SIZE);
			if (nbr == -1 || nbr == 0)
				break ;
			if (nbr > 0)
			{
				*(*buf + nbr) = 0;
				ft_traitements(buf, result, s1);
				if (*result)
					break ;
			}
		}
		free(*buf);
		return (nbr);
	}
	return (-1);
}

static void	my_free(char **s)
{
	free(*s);
	*s = 0;
}

char	*get_next_line(int fd)
{
	static char	*s1;
	char		*result;
	int			nbr;
	char		*buf;

	if (!s1)
		s1 = ft_strdup("");
	result = 0;
	nbr = my_read(fd, &buf, &result, &s1);
	if (nbr == -1)
		my_free(&s1);
	else if (nbr == 0)
	{
		ft_traitements(0, &result, &s1);
		if (!result && *s1 != '\0')
		{
			result = ft_strdup(s1);
			my_free(&s1);
		}
		else if (!result && *s1 == '\0')
			my_free(&s1);
	}
	return (result);
}
