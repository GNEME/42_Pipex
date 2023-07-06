/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 02:49:38 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/24 19:44:43 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}

static char	*my_join(char *str1, char *str2, int flag)
{
	size_t	str1_len;
	size_t	str2_len;
	size_t	i;
	char	*str;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	i = -1;
	str = malloc((str1_len + str2_len + 2) * sizeof(char));
	if (str)
	{
		while (++i < str1_len)
			str[i] = str1[i];
		str[i] = '/';
		i = -1;
		while (++i < str2_len)
			str[str1_len + 1 + i] = str2[i];
		str[str1_len + i + 1] = '\0';
	}
	if (!flag)
		str[str1_len + str2_len] = '\0';
	return (str);
}

static int	cmd_ispath(char *cmd, char **path)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '/')
		i ++;
	if (cmd[i] == '/')
	{
		*path = my_join(cmd, "", 0);
		return (1);
	}
	return (0);
}

static char	*my_whereis_norm(char *cmd, char *ptr, int *i, int *flag)
{
	char	*str;
	char	*path;

	str = ptr;
	path = my_join(str, cmd, 1);
	while (!file_exist(path) && *str)
	{
		if (*flag)
		{
			ptr[*i] = ':';
			*flag = 0;
			*i = *i + 1;
		}
		str = &ptr[*i];
		while (ptr[*i] != ':' && ptr[*i])
			*i = *i + 1;
		ptr[*i] = '\0';
		*flag = 1;
		if (path)
			free(path);
		path = my_join(str, cmd, 1);
	}
	return (path);
}

char	*my_whereis(char *envp_path, char *cmd)
{
	char	*ptr;
	char	*path;
	int		i;
	int		flag;

	path = 0;
	if (cmd_ispath(cmd, &path))
		return (path);
	ptr = my_join(&envp_path[5], "", 0);
	i = 0;
	flag = 0;
	if (ptr)
	{
		while (ptr[i] != ':' && ptr[i])
			i ++;
		ptr[i] = '\0';
		flag = 1;
		path = my_whereis_norm(cmd, ptr, &i, &flag);
		free(ptr);
		return (path);
	}
	return (0);
}
