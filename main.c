/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:28:22 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/15 12:37:30 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int argc, char *argv[], int index)
{
	if (argc <= 4)
	{
		write(1, "Not enough arguments\n", 21);
		exit(0);
	}
	else if (access(argv[1], F_OK))
	{
		perror("File 1 not found");
		exit (0);
	}
	else if (index == 0)
	{
		perror("File 2 not found");
		exit (0);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	**command;
	char	**path;
	int		i;

	path = 0;
	if (argc <= 4)
		error(argc, argv, 0);
	// if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	if (access(argv[1], F_OK))
		error(argc, argv, 1);
	command = malloc(sizeof(char *) * (argc - 3 + 2));
	i = 2;
	while (argv[i] && access(argv[i], F_OK))
	{
		command[i - 2] = ft_strdup(argv[i]);
		i++;
	}
	command[i - 2] = 0;
	// if (!argv[i])
	// 	argv[i] = ft_strdup(".");
	path = get_path(envp);
	launch(argc - 3, command, path, argv);
	return (0);
}
