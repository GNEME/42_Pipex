/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:53:55 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/30 21:54:22 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	openning(int ac, char **argv, int *infile_fd, int *outfile_fd)
{
	if (my_cmp(argv[1], "here_doc", 0, 0))
		*outfile_fd = open(argv[ac - 1], O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR);
	else
		*outfile_fd = open(argv[ac - 1], O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR);
	if (*outfile_fd == -1)
	{
		write_error_on_stderr(strerror(errno), argv[ac - 1], 1);
		exit(1);
	}
	if (*infile_fd == -1)
		exit (1);
	if (dup2(*infile_fd, STDIN_FILENO) == -1)
	{
		write_error_on_stderr(strerror(errno), 0, 0);
		exit (1);
	}
}
