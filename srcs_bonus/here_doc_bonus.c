/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:51:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/26 09:47:30 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <sys/types.h>
#include <sys/wait.h>

static void	check(void	*str, t_data *data)
{
	if (!str)
		destroy(&*data, 1, "Error\nMalloc error\n");
}

int	reading(int fd[2], t_data *data)
{
	char	*str;
	char	*new_str;

	str = 0;
	new_str = 0;
	close(fd[0]);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(data->limiter, str, ft_strlen(str)) == 0)
			break ;
		if (ft_strncmp("EOF", str, ft_strlen(str)) == 0)
			destroy(&*data, 0, 0);
		new_str = gnl_strjoin(new_str, str);
		if (!new_str)
			destroy(&*data, 1, "Error\nMalloc error\n");
		if (str != NULL)
			write(1, "pipe heredoc> ", 15);
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
}

void	here_doc(int argc, char *argv[], char **envp)
{
	t_data	data;
	int		i;

	if (argc <= 5)
		destroy(&data, 1, "Error\nWrong number of arguments\n");
	data.command = malloc(sizeof(char *) * (argc - 4 + 1));
	check(data.command, &data);
	i = 2;
	while (argv[i + 2])
	{
		data.command[i - 2] = ft_strdup(argv[i +1]);
		check(data.command[i - 2], &data);
		i++;
	}
	data.command[i - 2] = 0;
	data.limiter = ft_strjoin(argv[2], "\n");
	check(data.limiter, &data);
	data.start = STDIN_FILENO;
	data.end = open(argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	data.path = get_path(&data, envp);
	here_doc_launch(&data, argc - 3);
	destroy(&data, 0, 0);
	exit (1);
}
