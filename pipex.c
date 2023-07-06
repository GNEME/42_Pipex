/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:25:28 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/25 20:55:09 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	pipex_norm1(char **argvec, char *cmd, int *pipefd)
{
	pid_t	t;

	t = fork();
	if (t == -1)
	{
		write_error_on_stderr(strerror(errno), 0, 0);
		exit (1);
	}
	if (t == 0)
	{
		if (handle_cmd(argvec, cmd, pipefd))
		{
			if (errno == 2)
				write_error_on_stderr("command not found", argvec[0], 1);
			else
				write_error_on_stderr(strerror(errno), argvec[0], 1);
			exit(1);
		}
	}
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		write_error_on_stderr(strerror(errno), 0, 0);
		exit (1);
	}
}

static void	pipex_norm2(int ac, char **argv, char **envp, int *pipefd)
{
	char	**argvec;
	char	*cmd;
	int		i;

	i = 0;
	while (*envp != 0 && !my_cmp(*envp, "PATH=", 5, 1))
		envp ++;
	while (i < ac - 3)
	{
		if (*argv[2 + i])
		{
			if (pipe(pipefd) == -1)
			{
				write_error_on_stderr(strerror(errno), 0, 0);
				exit (1);
			}
			argvec = get_cmd(argv[2 + i]);
			cmd = my_whereis(*envp, argvec[0]);
			pipex_norm1(argvec, cmd, pipefd);
			close(pipefd[0]);
			free_argvec(argvec);
			free(cmd);
		}
		i ++;
	}
}

static void	pipex_norm3(int ac, char **argv, int *infile_fd, int *outfile_fd)
{
	if (ac != 5)
	{
		write_error_on_stderr("number of arguments should be 4 !", 0, 0);
		exit(1);
	}
	*infile_fd = open(argv[1], O_RDONLY);
	if (*infile_fd == -1)
		write_error_on_stderr(strerror(errno), argv[1], 1);
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

int	main(int ac, char **argv, char **envp)
{
	int	pipefd[2];
	int	infile_fd;
	int	outfile_fd;

	pipex_norm3(ac, argv, &infile_fd, &outfile_fd);
	close(infile_fd);
	pipex_norm2(ac, argv, envp, pipefd);
	while (read(STDIN_FILENO, &infile_fd, 1) > 0)
		write(outfile_fd, &infile_fd, 1);
	close(outfile_fd);
	waitpid(-1, NULL, 0);
	return (0);
}
