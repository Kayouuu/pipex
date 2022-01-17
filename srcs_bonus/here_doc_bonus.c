/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:51:15 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/17 16:22:40 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	here_doc_launch(char **path, char **commands, char *limiter, char *file)
{
	int		readed;
	int		limiter_size;
	char	*str;

	str = 0;
	readed = 0;
	write(1, "here_doc>", 10);
	while (1)
	{
		str = get_next_line(0);
		if (ft_strncmp(limiter, str, ft_strlen(limiter)) == 0)
			break ;	
		if (str != NULL)
			write(1, "here_doc>", 10);
	}
}

void	here_doc(char *argv[], char **envp)
{
	t_data	data;
	char	*commands[2];
	char	*limiter;
	char	*file;

	commands[0] = argv[3];
	commands[1] = argv[4];
	limiter = argv[2];
	file = argv[5];
	here_doc_launch(get_path(&data, envp), commands, limiter, file);
	exit (1);
}
