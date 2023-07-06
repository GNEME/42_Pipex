/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 21:03:11 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/25 21:05:45 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_argvec(char **argvec)
{
	char	**s;

	s = argvec;
	while (*s)
		free(*s ++);
	free(argvec);
}

void	write_error_on_stderr(char *str, char *path, int flag)
{
	write(2, "Pipex: ", 7);
	write(2, str, ft_strlen(str));
	if (flag)
	{
		write(2, ": ", 2);
		write(2, path, ft_strlen(path));
	}
	else
		(void)path;
	write(2, "\n", 1);
}

static void	get_len_and_allocate_norm(int *i_nbr, char *str,
	char **argvec, int *old_i)
{
	while (str[i_nbr[0]] == ' ' && str[i_nbr[0]])
		i_nbr[0]++;
	while (str[i_nbr[0]])
	{
		while (str[i_nbr[0]] != ' ' && str[i_nbr[0]])
			i_nbr[0]++;
		argvec[i_nbr[1]] = malloc((i_nbr[0] - *old_i + 1) * sizeof(char));
		if (!argvec[i_nbr[1]])
		{
			i_nbr[1]--;
			while (i_nbr[1] >= 0)
				free(argvec[i_nbr[1]--]);
			free(argvec);
			argvec = 0;
			return ;
		}
		i_nbr[1]++;
		while (str[i_nbr[0]] == ' ' && str[i_nbr[0]])
			i_nbr[0]++;
		*old_i = i_nbr[0];
	}
	argvec[i_nbr[1]] = 0;
}

static char	**get_len_and_allocate(char *str)
{
	int		i_nbr[2];
	int		old_i;
	char	**argvec;

	i_nbr[1] = 0;
	i_nbr[0] = 0;
	while (str[i_nbr[0]] == ' ' && str[i_nbr[0]])
		i_nbr[0]++;
	old_i = i_nbr[0];
	while (str[i_nbr[0]])
	{
		while (str[i_nbr[0]] != ' ' && str[i_nbr[0]])
			i_nbr[0]++;
		i_nbr[1]++;
		while (str[i_nbr[0]] == ' ' && str[i_nbr[0]])
			i_nbr[0]++;
	}
	argvec = malloc((i_nbr[1] + 1) * sizeof(char *));
	i_nbr[1] = 0;
	i_nbr[0] = 0;
	if (argvec)
		get_len_and_allocate_norm(i_nbr, str, argvec, &old_i);
	return (argvec);
}

char	**get_cmd(char *str)
{
	char	**argvec;
	int		i;
	int		j;
	int		nbr;

	argvec = get_len_and_allocate(str);
	if (argvec)
	{
		i = 0;
		nbr = 0;
		while (str[i] == ' ' && str[i])
			i ++;
		while (argvec[nbr])
		{
			j = 0;
			while (str[i] != ' ' && str[i])
				argvec[nbr][j++] = str[i++];
			argvec[nbr][j] = '\0';
			nbr ++;
			while (str[i] == ' ' && str[i])
				i ++;
		}
	}
	return (argvec);
}
