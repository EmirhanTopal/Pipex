/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:44 by marvin            #+#    #+#             */
/*   Updated: 2025/03/17 15:06:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*check_path(char **paths, char *cmd)
{
	int		j;
	char	*full_path;
	char	*temp_path;

	j = 0;
	while (paths[j])
	{
		temp_path = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!access(full_path, X_OK))
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

static char	*find_path(char **env, char **cmd)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths = ft_split(env[i] + 5, ':');
			return (check_path(paths, cmd[0]));
		}
		i++;
	}
	return (NULL);
}

static	void	child_process(int *fd, char **argv, char **env)
{
	int		open_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[0]);
	cmd = ft_split(argv[2], ' ');
	open_fd = open(argv[1], O_RDONLY);
	correct_path = find_path(env, cmd);
	if (open_fd == -1)
		return ;
	dup2(fd[1], STDOUT_FILENO);
	dup2(open_fd, STDIN_FILENO);
	close(fd[1]);
	if (execve(correct_path, cmd, env) == -1)
		write(1, "error execve", 13);
}

static	void	parent_process(int *fd, char **argv, char **env)
{
	int		read_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	read_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	correct_path = find_path(env, cmd);
	if (read_fd == -1)
		return ;
	dup2(fd[0], STDIN_FILENO);
	dup2(read_fd, STDOUT_FILENO);
	close(fd[0]);
	if (execve(correct_path, cmd, env) == -1)
		write(1, "error execve", 13);
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	my_pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			write(1, "error pipe", 11);
		my_pid = fork();
		if (my_pid == -1)
			write(1, "error pid", 10);
		if (my_pid == 0)
			child_process(fd, argv, env);
		parent_process(fd, argv, env);
	}
	return (0);
}
