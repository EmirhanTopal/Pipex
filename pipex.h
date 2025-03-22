/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:12:41 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 01:06:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	child_process(int *fd, char **argv, char **env);
void	parent_process(int *fd, char **argv, char **env);
int		child_new_process(void (*child_process)(int *, char **, char **),
			int *fd, char **argv, char **env);
int		parent_new_process(void (*parent_process)(int *, char **, char **),
			int *fd, char **argv, char **env);
char	*find_path(char **env, char **cmd);
char	*check_path(char **paths, char *cmd);
void	ft_error_and_exit(void);
void	ft_db_free(char **double_pointer);

#endif