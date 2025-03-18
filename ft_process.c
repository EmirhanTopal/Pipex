/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:20:10 by emtopal           #+#    #+#             */
/*   Updated: 2025/03/18 14:17:48 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **env)
{
	int		open_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[0]);
	cmd = ft_split(argv[2], ' ');
	open_fd = open(argv[1], O_RDONLY);
	if (open_fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	correct_path = find_path(env, cmd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(open_fd, STDIN_FILENO);
	close(fd[1]);
	if (execve(correct_path, cmd, env) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int *fd, char **argv, char **env)
{
	int		read_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	read_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	correct_path = find_path(env, cmd);
	if (read_fd == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(read_fd, STDOUT_FILENO);
	close(fd[0]);
	if (execve(correct_path, cmd, env) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
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
