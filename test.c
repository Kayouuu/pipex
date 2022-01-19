/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:58:37 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/19 09:48:57 by psaulnie         ###   ########.fr       */
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
		}
		ft_putstr_fd(new_str, fd[1]);
		return (0);
	}
	wait(NULL);
	dup2(fd[0], 0);
	close(fd[1]);
	execlp("cat", "cat", "-e", (char *)NULL);
}