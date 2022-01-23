/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:28:22 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/23 10:02:43 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error(int argc, char *argv[])
{
	if (argc != 5)
	{
		write(1, "Not enough arguments\n", 21);
		exit(0);
	}
	else if (access(argv[1], F_OK))
	{
		write(1, "File 1 not found", 17);
		exit (0);
	}
}

t_data	init(void)
{
	t_data	data;

	data.path = 0;
	data.command = 0;
	data.command = 0;
	data.final_path = NULL;
	data.old_stdout = dup(STDOUT_FILENO);
	data.start = -1;
	data.end = -1;
	return (data);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;
	int		i;

	error(argc, argv);
	data = init();
	data.command = malloc(sizeof(char *) * (argc - 3 + 2));
	if (!data.command)
		destroy(&data, 1, "Error\nMalloc error\n\0");
	i = 2;
	while (argv[i] && access(argv[i], F_OK))
	{
		data.command[i - 2] = ft_strdup(argv[i]);
		if (!data.command[i - 2])
			destroy(&data, 1, "Error\nMalloc error\n");
		i++;
	}
	data.command[i - 2] = 0;
	data.path = get_path(&data, envp);
	data.end = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	data.start = open(argv[1], O_RDONLY);
	launch(argc - 3, &data);
	destroy(&data, 0, 0);
	return (0);
}
