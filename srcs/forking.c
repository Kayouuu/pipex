/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:44:25 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/13 11:25:59 by psaulnie         ###   ########.fr       */
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
		printf("%s\n", data->command[i]);
		data->commands[i] = ft_split(data->command[i], ' ');
		i++;
	}
	data->commands[i] = NULL;
	forking(&*data, argv, cmd_num);
	free(data->final_path);
}

void	forking(t_data *data, char **argv, int cmd_num)
{
	data->fd.fdd = 0;
	while (*(data->commands) != NULL)
	{
		pipe(data->fd.fd);
		data->fd.pid = fork();
		if (data->fd.pid == -1)
			destroy(&*data, 1, "Error\nFork error\n\0");
		else if (data->fd.pid == 0)
		{
			if (*(data->commands) == (data->commands)[0])
				dup2(open(argv[1], O_RDONLY), 0);
			if (*(data->commands + 1) == NULL)
				dup2(open(argv[cmd_num + 2], FLAGS, 0666), 1);
			pipeline(&*data);
		}
		wait(NULL);
		close(data->fd.fd[1]);
		data->fd.fdd = data->fd.fd[0];
		data->commands = data->commands + 1;
	}
}

void	pipeline(t_data *data)
{
	dup2(data->fd.fdd, 0);
	if (*(data->commands) + 1 != NULL)
		dup2(data->fd.fd[1], 1);
	close(data->fd.fd[0]);
	if (data->final_path != 0)
		free(data->final_path);
	data->final_path = get_file_path(&*data);
	execve(data->final_path, &(*data->commands)[0], data->path);
	destroy(&*data, 1, "Error\nExecve failed\n\0");
}
