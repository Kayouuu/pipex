/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:51:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/22 11:38:45 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

int	reading(int fd[2])
{
	char	*str;
	char	*new_str;

	str = 0;
	new_str = 0;
	close(fd[0]);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp("eof", str, 3) == 0)
			break ;
		new_str = gnl_strjoin(new_str, str);
		if (str != NULL)
			write(1, "pipe here_doc> ", 16);
		free(str);
	}
	free(str);
	ft_putstr_fd(new_str, fd[1]);
	free(new_str);
	return (0);
}

void	here_doc_launch(t_data *data, int cmd_nbr)
{
	int		i;

	i = 0;
	data->commands = malloc(sizeof(char **) * (cmd_nbr + 1));
	if (!data->commands)
		destroy(&*data, 1, "Error\nMalloc error\n");
	while (i < cmd_nbr)
	{
		data->commands[i] = ft_split(data->command[i], ' ');
		i++;
	}
	data->commands[i] = NULL;
	forking_here_doc(&*data);
	// free(data->final_path);
}

void	here_doc(int argc, char *argv[], char **envp)
{
	t_data	data;
	int		i;

	if (argc <= 5)
	{
		ft_putstr_fd("Error\nWrong number of arguments\n", 1);
		exit(-1);
	}
	data.command = malloc(sizeof(char *) * (argc - 4 + 1));
	if (!data.command)
		destroy(&data, 1, "Error\nMalloc error\n\0");
	i = 2;
	while (argv[i + 2])
	{
		data.command[i - 2] = ft_strdup(argv[i +1]);
		i++;
	}
	data.command[i - 2] = 0;
	data.limiter = argv[2];
	data.start = STDIN_FILENO;
	data.end = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	data.path = get_path(&data, envp);
	here_doc_launch(&data, argc - 3);
	// destroy(&data, 0, 0);
	exit (1);
}
