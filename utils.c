/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtopal <emtopal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:43:11 by emtopal           #+#    #+#             */
/*   Updated: 2025/02/04 17:03:13 by emtopal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s12_len;
	char		*ptr;
	size_t		i;
	size_t		j;

	s12_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1 + ft_strlen(s2)));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ((size_t) ft_strlen(s1)))
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i < (s12_len))
	{
		ptr[i] = s2[j];
		j++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		i++;
	}
	return ((unsigned char )s1[i] - (unsigned char )s2[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	free_dd_array(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
		{
			if (str[i])
				free(str[i]);
		}
		free(str);
	}
}
