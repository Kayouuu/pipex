/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:28:22 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/13 15:52:28 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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

t_data	init(void)
{
	t_data	data;

	data.path = 0;
	data.command = 0;
	data.command = 0;
	data.final_path = 0;
	data.old_stdin = dup(STDIN_FILENO);
	return (data);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;
	int		i;

	if (argc <= 4)
		error(argc, argv, 0);
	if (access(argv[1], F_OK))
		error(argc, argv, 1);
	data = init();
	data.command = malloc(sizeof(char *) * (argc - 3 + 2));
	if (!data.command)
		destroy(&data, 1, "Error\nMalloc error\n\0");
	i = 2;
	while (argv[i] && access(argv[i], F_OK))
	{
		data.command[i - 2] = ft_strdup(argv[i]);
		i++;
	}
	data.command[i - 2] = 0;
	data.path = get_path(&data, envp);
	launch(argc - 3, &data, argv);
	return (0);
}
