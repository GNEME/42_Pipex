/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:45:23 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/29 02:26:36 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i ++;
	return (i);
}

int	my_cmp(char *env, char *str, int nbr, int check_str_in_env)
{
	int	i;

	i = 0;
	if (check_str_in_env)
	{
		while (env[i] == str[i] && i < nbr)
			i ++;
		if (i == nbr)
			return (1);
		return (0);
	}
	else
	{
		(void)nbr;
		while (env[i] && str[i] && env[i] == str[i])
			i ++;
		if (!env[i] && !str[i])
			return (1);
		return (0);
	}
}

int	handle_cmd(char **argvec, char *cmd, int *pipefd)
{
	char	*env[1];

	env[0] = NULL;
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	return (execve(cmd, argvec, env) == -1);
}
