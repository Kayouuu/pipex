/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:33:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/13 11:15:15 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	destroy(t_data *data, int has_error, char *error_msg)
{
	int	i;

	i = 0;
	error_msg = 0;
	if (has_error)
		write(data->fd.fd[1], "AAAA", 4);
	// 	write(1, &error_msg, ft_strlen(error_msg));
	if (data->path != 0)
		free_tab(data->path);
	if (data->command != 0)
		free_tab(data->command);
	if (data->commands != 0)
	{
		while (data->commands[i] != 0)
		{
			free_tab(data->commands[i]);
			i++;
		}
		//free(data->commands);
	}
	exit(0);
}
