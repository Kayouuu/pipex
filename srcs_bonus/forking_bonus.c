/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:44:25 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/26 14:05:23 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

void	process_wait(t_data *data)
{
	int	i;

	i = 0;
	while ((data->commands[i]) != NULL)
	{
		wait(NULL);
		i++;
	}
}

void	launch(int cmd_num, t_data *data)
{
	int		i;

	i = 0;
	data->commands = malloc(sizeof(char **) * (cmd_num + 1));
	if (!data->commands)
		destroy(&*data, 1, "Error\nMalloc error\n");
	while (i < cmd_num)
	{
		if (ft_strlen(data->command[i]) > 1)
			data->commands[i] = ft_split(data->command[i], ' ');
		else
		{
			data->commands[i] = malloc(sizeof(char *) * 2);
			if (!data->commands[i])
				destroy(&*data, 1, "Error\nMalloc error\n");
			data->commands[i][0] = ft_strdup(data->command[i]);
			data->commands[i][1] = NULL;
		}
		if (!data->commands[i])
			destroy(&*data, 1, "Error\nMalloc error\n");
		i++;
	}
	data->commands[i] = NULL;
	forking(&*data);
}

void	forking(t_data *data)
{
	int	i;

	i = 0;
	data->fd.fdd = 0;
	while ((data->commands[i]) != NULL)
	{
		if (pipe(data->fd.fd) == -1)
			destroy(&*data, 1, "Pipe error");
		data->fd.pid = fork();
		if (data->fd.pid == -1)
			destroy(&*data, 1, "Error\nFork error\n\0");
		else if (data->fd.pid == 0)
		{
			pipeline(&*data, i);
		}
		free(data->final_path);
		if (close(data->fd.fd[1]) == -1)
			destroy(&*data, 1, "Error\nClose error\n");
		data->fd.fdd = data->fd.fd[0];
		i++;
	}
	process_wait(&*data);
}

void	pipeline(t_data *data, int i)
{
	if (i == 0)
		if (dup2(data->start, 0) == -1)
			destroy(&*data, 1, "Error\nDup error\n");
	if (data->commands[i + 1] == NULL)
		if (dup2(data->end, 1) == -1)
			destroy(&*data, 1, "Error\nDup error\n");
	if (dup2(data->fd.fdd, 0) == -1)
		destroy(&*data, 1, "Error\nDup error\n");
	if (data->commands[i + 1] != NULL)
		if (dup2(data->fd.fd[1], 1) == -1)
			destroy(&*data, 1, "Error\nDup error\n");
	if (close(data->fd.fd[0]) == -1)
		destroy(&*data, 1, "Error\nClose error\n");
	data->final_path = get_file_path(&*data, i);
	execve(data->final_path, &data->commands[i][0], data->path);
	destroy(&*data, 1, "Error\nExecve failed\n\0");
}
