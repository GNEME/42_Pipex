/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:23:13 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/29 02:52:28 by ggneme           ###   ########.fr       */
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

	if (my_cmp(argv[1], "here_doc", 0, 0))
		i = 2;
	else
		i = 1;
	while (++i < ac - 1)
	{
		if (*argv[i])
		{
			if (pipe(pipefd) == -1)
			{
				write_error_on_stderr(strerror(errno), 0, 0);
				exit (1);
			}
			argvec = get_cmd(argv[i]);
			cmd = my_whereis(*envp, argvec[0]);
			pipex_norm1(argvec, cmd, pipefd);
			close(pipefd[0]);
			free_argvec(argvec);
			free(cmd);
		}
	}
}

static int	handle_heredoc(char **argv)
{
	char	*line;
	size_t	len;
	int		tmp_fd;

	tmp_fd = open(".here_doc.tmp", O_RDWR | O_TRUNC
			| O_CREAT, S_IRUSR | S_IWUSR);
	if (tmp_fd == -1)
		exit(1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			break ;
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (my_cmp(line, argv[2], 0, 0))
			break ;
		line[len - 1] = '\n';
		write(tmp_fd, line, len);
		free(line);
	}
	if (line)
		free(line);
	return (tmp_fd);
}

static void	pipex_norm3(int ac, char **argv, int *infile_fd, int *outfile_fd)
{
	if (!my_cmp(argv[1], "here_doc", 0, 0))
	{
		*infile_fd = open(argv[1], O_RDONLY);
		if (*infile_fd == -1)
			write_error_on_stderr(strerror(errno), argv[1], 1);
		openning(ac, argv, infile_fd, outfile_fd);
	}
	else
	{
		close(handle_heredoc(argv));
		*infile_fd = open(".here_doc.tmp", O_RDONLY);
		if (*infile_fd == -1)
			write_error_on_stderr(strerror(errno), "here_doc", 1);
		openning(ac, argv, infile_fd, outfile_fd);
	}
}

int	main(int ac, char **argv, char **envp)
{
	int	pipefd[2];
	int	infile_fd;
	int	outfile_fd;

	if (ac < 2)
		return (1);
	pipex_norm3(ac, argv, &infile_fd, &outfile_fd);
	close(infile_fd);
	if (my_cmp(argv[1], "here_doc", 0, 0))
	{
		if (unlink(".here_doc.tmp") == -1)
		{
			write_error_on_stderr(strerror(errno), 0, 0);
			exit (1);
		}
	}
	while (*envp != 0 && !my_cmp(*envp, "PATH=", 5, 1))
		envp ++;
	pipex_norm2(ac, argv, envp, pipefd);
	while (read(STDIN_FILENO, &infile_fd, 1) > 0)
		write(outfile_fd, &infile_fd, 1);
	close(outfile_fd);
	waitpid(-1, NULL, 0);
	return (0);
}
