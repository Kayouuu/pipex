/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:51:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/19 12:07:59 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

int	forking_here_doc(t_data *data)
{
	int		i;
	int		fd[2];
	pid_t	pid;

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
			{
				pipe(fd);
				pid = fork();
				if (pid == 0)
					return (reading(fd, &*data));
				else
				{
					wait(NULL);
					dup2(fd[0], data->fd.fd[1]);
					close(data->fd.fd[1]);
				}
				dup2(data->fd.fd[0], 0);
			}
			pipeline_here_doc(&*data, i);
		}
		wait(NULL);
		close(data->fd.fd[1]);
		data->fd.fdd = data->fd.fd[0];
		i++;
	}
	process_wait(&*data);
	return (1);
}

void	pipeline_here_doc(t_data *data, int i)
{
	dup2(data->fd.fdd, 0);
	//if (data->commands[i + 1] != NULL)
		dup2(data->fd.fd[1], 1);
	//close(data->fd.fd[0]);
	if (data->final_path != 0)
		free(data->final_path);
	data->final_path = get_file_path(&*data, i);
	ft_putstr_fd("A", 2);
	if (data->commands[i + 1] == NULL)
		dup2(data->end, 1);
	execve(data->final_path, &data->commands[i][0], data->path);
	destroy(&*data, 1, "Error\nExecve failed\n\0");
}

int	reading(int fd[2], t_data *data)
{
	char	*str;
	char	*new_str;

	str = 0;
	new_str = 0;
	close(fd[0]);
	data->start = fd[0];
	write(1, "pipe here_doc> ", 16);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(data->limiter, str, 3) == 0)
			break ;
		new_str = gnl_strjoin(new_str, str);
		if (str != NULL)
			write(1, "pipe here_doc> ", 16);
		free(str);
	}
	ft_putstr_fd(new_str, fd[1]);
	return (0);
}

void	here_doc_launch(t_data *data)
{
	int		i;

	i = 0;
	data->commands = malloc(sizeof(char **) * (2 + 1));
	if (!data->commands)
		destroy(&*data, 1, "Error\nMalloc error\n");
	while (i < 2)
	{
		data->commands[i] = ft_split(data->command[i], ' ');
		i++;
	}
	data->commands[i] = NULL;
	forking_here_doc(&*data);
	free(data->final_path);
	free(data->final_path);
}

void	here_doc(int argc, char *argv[], char **envp)
{
	t_data	data;

	if (argc != 6)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 1);
		exit(-1);
	}
	data.command = malloc(sizeof(char *) * (2 + 1));
	data.command[0] = argv[3];
	data.command[1] = argv[4];
	data.command[2] = 0;
	data.limiter = argv[2];
	data.start = STDIN_FILENO;
	data.end = open(argv[5], O_RDWR | O_CREAT | O_TRUNC, 0666);
	data.path = get_path(&data, envp);
	here_doc_launch(&data);
	//destroy(&data, 0, 0);
	exit (1);
}
