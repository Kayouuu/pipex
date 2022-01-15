/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:01:42 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/15 16:46:34 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/libft.h"

# define FLAGS O_RDWR | O_CREAT | O_TRUNC

typedef struct s_fd
{
	int		fd[2];
	int		fdd;
	pid_t	pid;
}	t_fd;

typedef struct s_data
{
	t_fd	fd;
	char	***commands;
	char	**command;
	char	**path;
	char	*final_path;
	int		old_stdin;
}	t_data;

/*	MAIN.C	*/

void	error(int argc, char *argv[], int index);

/*	DESTROY.C	*/

void	destroy(t_data *data, int has_error, char *error_msg);

/*	FORKING.C	*/

void	launch(int cmd_num, t_data *data, char **argv);
void	forking(t_data *data, char **argv, int cmd_num);
void	pipeline(t_data *data, int i);

/*	PATH.C	*/

char	**get_path(t_data *data, char **envp);
char	*get_file_path(t_data *data, int cmd_num);

#endif