/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:44:25 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/15 16:47:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	launch(int cmd_num, t_data *data, char **argv)
{
	int		i;

	i = 0;
	data->commands = malloc(sizeof(char **) * (cmd_num + 1));
	if (!data->commands)
		destroy(&*data, 1, "Error\nMalloc error\n");
	while (i < cmd_num)
	{
		data->commands[i] = ft_split(data->command[i], ' ');
		i++;
	}
	data->commands[i] = NULL;
	forking(&*data, argv, cmd_num);
	free(data->final_path);
}

void	forking(t_data *data, char **argv, int cmd_num)
{
	int	i;

	i = 0;
	data->fd.fdd = 0;
	while ((data->commands[i]) != NULL)
	{
		pipe(data->fd.fd);
		data->fd.pid = fork();
		if (data->fd.pid == -1)
			destroy(&*data, 1, "Error\nFork error\n\0");
		else if (data->fd.pid == 0)
		{
			if (i == 0)
				dup2(open(argv[1], O_RDONLY), 0);
			if (data->commands[i + 1] == NULL)
			{
				dup2(open(argv[cmd_num + 2], FLAGS, 0666), 1);
			}
			pipeline(&*data, i);
		}
		wait(NULL);
		close(data->fd.fd[1]);
		data->fd.fdd = data->fd.fd[0];
		i++;
	}
}

void	pipeline(t_data *data, int i)
{
	dup2(data->fd.fdd, 0);
	if (data->commands[i + 1] != NULL)
		dup2(data->fd.fd[1], 1);
	close(data->fd.fd[0]);
	if (data->final_path != 0)
		free(data->final_path);
	data->final_path = get_file_path(&*data, i);
	execve(data->final_path, &data->commands[i][0], data->path);
	destroy(&*data, 1, "Error\nExecve failed\n\0");
}
