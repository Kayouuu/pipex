/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:58:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/21 10:16:48 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

int main()
{
	char	*str;
	char	*new_str;
	int		pid;
	int		fd[2];

	new_str = 0;
	str = 0;
	write(1, "pipe here_doc>", 15);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			str = get_next_line(0);
			if (ft_strncmp("eof", str, 3) == 0)
				break ;
			new_str = gnl_strjoin(new_str, str);
			if (str != NULL)
				write(1, "pipe here_doc>", 15);
			free(str);
		}
		free(str);
		ft_putstr_fd(new_str, fd[1]);
		free(new_str);
		return (0);
	}
	int fdd = fd[0];
	wait(NULL);
	fd[0] = fdd;
	dup2(fdd, 0);
	close(fd[1]);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		execlp("tr", "tr", "a-z", "A-Z", (char *)NULL);
		ft_putstr_fd("nul a chier\n", 2);
	}
	wait(NULL);
	close(fd[1]);
	fdd = fd[0];
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(open("outfile", O_CREAT | O_TRUNC | O_WRONLY, 0666), 1);
		dup2(fdd, 0);
		close(fd[0]);
		execlp("cat", "cat", "-e", (char *)NULL);
		ft_putstr_fd("grosse merde\n", 2);
	}
	wait(NULL);
	close(fd[1]);
}