/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 01:04:04 by marvin            #+#    #+#             */
/*   Updated: 2025/03/23 01:04:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_db_free(char **double_pointer)
{
	int	i;

	i = 0;
	while (double_pointer[i])
	{
		free(double_pointer[i]);
		i++;
	}
	free(double_pointer);
}
