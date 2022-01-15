/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 10:33:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/15 17:31:17 by psaulnie         ###   ########.fr       */
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
	dup2(data->old_stdout, STDOUT_FILENO);
	close(data->old_stdout);
	if (has_error)
		ft_putstr_fd(error_msg, 1);
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
		free(data->commands);
	}
	if (data->start != -1)
		close(data->start);
	if (data->end != -1)
		close(data->end);
	exit(0);
}
