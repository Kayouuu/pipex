/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:51:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/12 14:15:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"
#include <limits.h>

void	here_doc_launch(char **path, char **commands, char *limiter, char *file)
{
	int		readed;
	int		first_time;
	int		pid;
	int		fd[2];
	int		fdd;
	char	buffer[1];
	char	*str;

	first_time = 1;
	str = 0;
	fdd = 0;
	while (ft_memcmp(buffer, limiter, readed) != 0 || first_time == 1)
	{
		pipe(fd);
		first_time = 0;
		readed = 0;
		write(1, "here_doc>", 10);
		while (readed == 0)
			readed = read(0, buffer, 1);
		buffer[readed] = '\0';
	}
}

void	here_doc(char *argv[], char **envp)
{
	char	*commands[2];
	char	*limiter;
	char	*file;

	commands[0] = argv[3];
	commands[1] = argv[4];
	limiter = argv[2];
	file = argv[5];
	if (access(file, F_OK))
	{
		perror("File not found");
		exit(0);
	}
	here_doc_launch(get_path(envp), commands, limiter, file);
	exit (1);
}
