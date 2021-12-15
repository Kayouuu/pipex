/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:44:25 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/15 14:01:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	launch(int cmd_num, char **command, char **path, char **argv)
{
	int		i;
	char	***commands;

	i = 0;
	commands = malloc(sizeof(char **) * (cmd_num + 1));
	if (!commands)
	{
		perror("malloc");
		exit(1);
	}
	while (i < cmd_num)
	{
		if (i == 0)
			commands[i] = first_split(command[i], ' ', argv[1]);
		else
			commands[i] = ft_split(command[i], ' ');
		i++;
	}
	commands[i] = NULL;
	forking(commands, path, argv[cmd_num + 2]);
}

void	forking(char ***cmd, char **path, char *write_file)
{
	int		fd[2];
	pid_t	pid;
	int		fdd;

	fdd = 0;
	while (*cmd != NULL)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			if (*(cmd + 1) == NULL)
				dup2(open(write_file, O_RDWR | O_CREAT, 0666), 1);
			pipeline(fdd, fd, cmd, path);
		}
		wait(NULL);
		close(fd[1]);
		fdd = fd[0];
		cmd++;
	}
}

void	pipeline(int fdd, int *fd, char ***cmd, char **path)
{
	dup2(fdd, 0);
	if (*(cmd + 1) != NULL)
		dup2(fd[1], 1);
	close(fd[0]);
	execve(get_file_path(*cmd, path), &(*cmd)[0], path);
	perror("execve failed");
	exit(1);
}
