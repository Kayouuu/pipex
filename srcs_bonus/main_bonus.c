/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:28:22 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/26 10:26:51 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	error(int argc, char *argv[])
{
	if (argc < 5)
	{
		ft_putstr_fd("Error\nNot enough arguments\n", 2);
		exit(0);
	}
	else if (access(argv[1], F_OK)
		&& ft_memcmp("here_doc", argv[1], ft_strlen(argv[1])) != 0)
	{
		ft_putstr_fd("Error\nFile 1 not found", 2);
		exit (0);
	}
}

static void	check(t_data *data)
{
	if (data->start == -1)
	{
		free_tab(data->command);
		ft_putstr_fd("Error\nNo file permission\n", 2);
		exit(-1);
	}
}

t_data	init(int argc, char *argv[])
{
	t_data	data;

	data.path = 0;
	data.command = 0;
	data.command = 0;
	data.final_path = 0;
	data.limiter = 0;
	data.final_path = 0;
	data.old_stdout = dup(STDOUT_FILENO);
	data.start = -1;
	data.end = -1;
	error(argc, argv);
	return (data);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data	data;
	int		i;

	data = init(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		here_doc(argc, argv, envp);
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
	data.start = open(argv[1], O_RDONLY);
	check(&data);
	data.end = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	launch(argc - 3, &data);
	destroy(&data, 0, 0);
	return (0);
}
