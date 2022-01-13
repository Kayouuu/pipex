/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:28:22 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/10 17:31:06 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(argv, envp);
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
	path = get_path(envp);
	launch(argc - 3, command, path, argv);
	return (0);
}
