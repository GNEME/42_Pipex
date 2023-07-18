/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggneme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:24 by ggneme            #+#    #+#             */
/*   Updated: 2023/03/29 02:39:23 by ggneme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define BUFFER_SIZE 42
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

size_t	ft_strlen(const char *str);
char	*my_whereis(char *envp_path, char *cmd);
void	free_argvec(char **argvec);
void	write_error_on_stderr(char *str, char *path, int flag);
char	**get_cmd(char *str);
int		handle_cmd(char **argvec, char *cmd, int *pipefd);
int		my_cmp(char *env, char *str, int nbr, int check_str_in_env);
void	openning(int ac, char **argv, int *infile_fd, int *outfile_fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);
#endif
