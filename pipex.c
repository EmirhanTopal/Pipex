/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:42:54 by emtopal           #+#    #+#             */
/*   Updated: 2025/02/04 19:15:14 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_error(char **cmd, int open_fd)
{
	if (open_fd != -1)
		close(open_fd);
	free_dd_array(cmd);
	exit(EXIT_FAILURE);
}

static char	*find_path(char **env, char **cmd)
{
	int		i;
	int		j;
	char	**paths;
	char	*full_path;
	char	*temp_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	j = -1;
	while (paths[++j] != NULL)
	{
		temp_path = ft_strjoin(paths[j], "/");
		full_path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (free_dd_array(paths), full_path);
		free(full_path);
	}
	free_dd_array(paths);
	return (NULL);
}

static void	child_process(int *fd, char **argv, char **env)
{
	int		open_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[0]);
	cmd = ft_split(argv[2], ' ');
	open_fd = open(argv[1], O_RDONLY);
	if (open_fd == -1)
		ft_error(cmd, open_fd);
	correct_path = find_path(env, cmd);
	if (correct_path == NULL)
		ft_error(cmd, open_fd);
	dup2(fd[1], STDOUT_FILENO);
	dup2(open_fd, STDIN_FILENO);
	close(fd[1]);
	close(open_fd);
	if (!cmd[0] || !cmd)
		exit(EXIT_FAILURE);
	if (execve(correct_path, cmd, env) == -1)
	{
		free(correct_path);
		free_dd_array(cmd);
		exit(EXIT_FAILURE);
	}
}

static void	parent_process(int *fd, char **argv, char **env)
{
	int		read_fd;
	char	**cmd;
	char	*correct_path;

	close(fd[1]);
	cmd = ft_split(argv[3], ' ');
	if (!cmd[0] || !cmd)
		exit(EXIT_FAILURE);
	read_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (read_fd == -1)
		ft_error(cmd, read_fd);
	correct_path = find_path(env, cmd);
	if (correct_path == NULL)
		ft_error(cmd, read_fd);
	dup2(fd[0], STDIN_FILENO);
	dup2(read_fd, STDOUT_FILENO);
	close(fd[0]);
	close(read_fd);
	if (execve(correct_path, cmd, env) == -1)
	{
		free(correct_path);
		free_dd_array(cmd);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	mypid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			printf("error pipe");
		mypid = fork();
		if (mypid == -1)
			printf("error pid");
		if (mypid == 0)
			child_process(fd, argv, env);
		parent_process(fd, argv, env);
	}
	return (0);
}
