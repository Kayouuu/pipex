/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:31:32 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/26 13:24:47 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

int	forking_here_doc(t_data *data)
{
	int		i;

	i = 0;
	write(1, "pipe heredoc> ", 15);
	if (pipe(data->fd.fd) == -1)
		destroy(&*data, 1, "Error\nPipe error\n\0");
	data->fd.pid = fork();
	if (data->fd.pid == -1)
		destroy(&*data, 1, "Error\nFork error\n\0");
	if (data->fd.pid == 0)
		return (reading(data->fd.fd, &*data));
	data->fd.fdd = data->fd.fd[0];
	wait(NULL);
	data->fd.fd[0] = data->fd.fdd;
	if (dup2(data->fd.fdd, 0) == -1)
		destroy(&*data, 1, "Error\nDup error\n");
	if (close(data->fd.fd[1]) == -1)
		destroy(&*data, 1, "Error\nClose error\n");
	data->fd.fdd = data->fd.fd[0];
	while ((data->commands[i]) != NULL)
		i = process(&*data, i);
	process_wait(&*data);
	return (0);
}

int	process(t_data *data, int i)
{
	if (pipe(data->fd.fd) == -1)
		destroy(&*data, 1, "Error\nPipe error\n");
	data->fd.pid = fork();
	if (data->fd.pid == -1)
		destroy(&*data, 1, "Error\nFork error\n");
	else if (data->fd.pid == 0)
		return (execute_here_doc(&*data, i));
	if (close(data->fd.fd[1]) == -1)
		destroy(&*data, 1, "Error\nClose error\n");
	data->fd.fdd = data->fd.fd[0];
	return (i + 1);
}

int	execute_here_doc(t_data *data, int i)
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
	data->final_path = 0;
	data->final_path = get_file_path(&*data, i);
	execve(data->final_path, &data->commands[i][0], data->path);
	destroy(&*data, 1, "Error\nExecve failed\n\0");
	return (0);
}
