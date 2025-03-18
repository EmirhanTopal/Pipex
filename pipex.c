/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:06:44 by marvin            #+#    #+#             */
/*   Updated: 2025/03/18 14:17:36 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error_and_exit(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

char	*check_path(char **paths, char *cmd)
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
		if (!access(full_path, X_OK | F_OK))
			return (full_path);
		free(full_path);
		j++;
	}
	return (NULL);
}

char	*find_path(char **env, char **cmd)
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

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pidc;
	pid_t	pidp;

	if (argc == 5)
	{
		if (argv[3][0] == '\0' || argv[2][0] == '\0')
			ft_error_and_exit();
		if (pipe(fd) == -1)
			ft_error_and_exit();
		pidc = child_new_process(child_process, fd, argv, env);
		pidp = parent_new_process(parent_process, fd, argv, env);
		close(fd[1]);
		close(fd[0]);
		waitpid(pidc, NULL, 0);
		waitpid(pidp, NULL, 0);
	}
	else
		write(2, "error argument count", 21);
	return (0);
}
