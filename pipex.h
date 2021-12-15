/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:01:42 by psaulnie          #+#    #+#             */
/*   Updated: 2021/12/15 10:05:45 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libft/libft.h"

typedef struct s_fd
{
	int	fd[2];
	int	fdd;
}	t_fd;

/*	MAIN.C	*/

void	error(int argc, char *argv[], int index);

/*	FIRST_SPLIT.C	*/

char	**first_split(char const *s, char c, char *read_file);

/*	FORKING.C	*/

void	launch(int cmd_num, char **command, char **path, char **argv);
void	forking(char ***cmd, char **path, char *write_file);
void	pipeline(int fdd, int *fd, char ***cmd, char **path);

/*	PATH.C	*/

char	**get_path(char **envp);
char	*get_file_path(char **command, char **path);

#endif