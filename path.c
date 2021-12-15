/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:05:56 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/13 13:54:36 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	int		i;
	char	*path;
	char	**splitted_path;

	i = 0;
	while (envp[i] != '\0')
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_strdup(ft_strnstr(envp[i], "PATH=", 5) + 5);
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		perror("No PATH found");
		exit (0);
	}
	splitted_path = ft_split(path, ':');
	free(path);
	return (splitted_path);
}

char	*get_file_path(char **command_line, char **path)
{
	char	*file_path;
	int		i;

	i = 0;
	file_path = ft_strjoin(ft_strjoin(path[i], "/"), command_line[0]);
	while (path[i] && access(file_path, F_OK))
	{
		free(file_path);
		file_path = ft_strjoin(ft_strjoin(path[i], "/"), command_line[0]);
		i++;
	}
	if (!access(file_path, F_OK))
		return (file_path);
	else
	{
		perror("UNIX Command not found");
		exit(0);
	}
}
