/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:27:39 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/26 09:47:37 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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

void	free_all(t_data *data)
{
	if (data->path != 0)
		free_tab(data->path);
	if (data->command != 0)
		free_tab(data->command);
	if (data->end != -1)
		close(data->end);
	if (data->start != -1)
		close(data->start);
	if (data->limiter != 0)
		free(data->limiter);
}

void	destroy(t_data *data, int has_error, char *error_msg)
{
	int	i;

	i = 0;
	waitpid(data->fd.pid, NULL, WUNTRACED);
	if (has_error)
		ft_putstr_fd(error_msg, 2);
	free_all(&*data);
	if (data->commands != 0)
	{
		while (data->commands[i])
		{
			free_tab(data->commands[i]);
			i++;
		}
		free(data->commands);
	}
	exit(0);
}
