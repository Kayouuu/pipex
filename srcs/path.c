/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:05:56 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/23 10:08:56 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	check(void	*str, t_data *data)
{
	if (!str)
		destroy(&*data, 1, "Error\nMalloc error\n");
}

char	**get_path(t_data *data, char **envp)
{
	int		i;
	char	*path;
	char	**splitted_path;

	i = 0;
	path = 0;
	while (envp[i] != '\0')
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path = ft_strdup(ft_strnstr(envp[i], "PATH=", 5) + 5);
			if (!path)
				destroy(&*data, 1, "Error\nMalloc error\n");
			break ;
		}
		i++;
	}
	if (!envp[i])
		destroy(&*data, 1, "Error\nPATH not found\n\0");
	splitted_path = ft_split(path, ':');
	if (!splitted_path)
		destroy(&*data, 1, "Error\nMalloc error\n");
	free(path);
	return (splitted_path);
}

char	*get_file_path(t_data *data, int cmd_num)
{
	char	*file_path;
	char	*path;
	int		i;

	i = 0;
	path = ft_strjoin(data->path[i], "/");
	check(path, &*data);
	file_path = ft_strjoin(path, data->commands[cmd_num][0]);
	check(file_path, &*data);
	free(path);
	while (data->path[i] && access(file_path, F_OK))
	{
		free(file_path);
		path = ft_strjoin(data->path[i], "/");
		check(path, &*data);
		file_path = ft_strjoin(path, data->commands[cmd_num][0]);
		check(file_path, &*data);
		i++;
	}
	free(path);
	if (!access(file_path, F_OK))
		return (file_path);
	destroy(&*data, 1, "Error\nUNIX Command not found\n");
	exit(1);
}
