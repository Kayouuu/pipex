/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:44:25 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/11 11:34:50 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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
		commands[i] = ft_split(command[i], ' ');
		i++;
	}
	commands[i] = NULL;
	forking(commands, path, argv, cmd_num);
}

void	forking(char ***cmd, char **path, char **argv, int cmdnb)
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
			if (*cmd == cmd[0])
				dup2(open(argv[1], O_RDONLY), 0);
			if (*(cmd + 1) == NULL)
				dup2(open(argv[cmdnb + 2], O_RDWR | O_CREAT | O_TRUNC, 438), 1);
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
