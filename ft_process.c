/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:20:10 by emtopal           #+#    #+#             */
/*   Updated: 2025/03/23 01:14:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **env)
{
	int		open_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[0]);
	open_fd = open(argv[1], O_RDONLY);
	if (open_fd == -1)
		ft_error_and_exit();
	cmd = ft_split(argv[2], ' ');
	correct_path = find_path(env, cmd);
	if (!correct_path)
	{
		ft_db_free(cmd);
		ft_error_and_exit();
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(open_fd, STDIN_FILENO);
	close(fd[1]);
	if (execve(correct_path, cmd, env) == -1)
	{
		ft_error_and_exit();
	}
}

void	parent_process(int *fd, char **argv, char **env)
{
	int		read_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[1]);
	read_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (read_fd == -1)
		ft_error_and_exit();
	cmd = ft_split(argv[3], ' ');
	correct_path = find_path(env, cmd);
	if (!correct_path)
	{
		ft_db_free(cmd);
		ft_error_and_exit();
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(read_fd, STDOUT_FILENO);
	close(fd[0]);
	if (execve(correct_path, cmd, env) == -1)
	{
		ft_error_and_exit();
	}
}

int	child_new_process(void (*child_process)(int *, char **, char **)
				, int *fd, char **argv, char **env)
{
	pid_t	my_pid;

	my_pid = fork();
	if (my_pid == -1)
		perror("Error");
	if (my_pid == 0)
		child_process(fd, argv, env);
	return (my_pid);
}

int	parent_new_process(void (*parent_process)(int *, char **, char **)
				, int *fd, char **argv, char **env)
{
	pid_t	my_pid;

	my_pid = fork();
	if (my_pid == -1)
		perror("Error");
	if (my_pid == 0)
		parent_process(fd, argv, env);
	return (my_pid);
}
