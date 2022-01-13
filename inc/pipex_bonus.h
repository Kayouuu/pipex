/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:01:42 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/10 17:31:00 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/libft.h"

typedef struct s_fd
{
	int	fd[2];
	int	fdd;
}	t_fd;

/*	MAIN_BONUS.C	*/

void	error(int argc, char *argv[], int index);

/*	FORKING_BONUS.C	*/

void	launch(int cmd_num, char **command, char **path, char **argv);
void	forking(char ***cmd, char **path, char **argv, int cmd_num);
void	pipeline(int fdd, int *fd, char ***cmd, char **path);

/*	HERE_DOC_BONUS.C	*/

void	here_doc(char *argv[], char **envp);

/*	PATH_BONUS.C	*/

char	**get_path(char **envp);
char	*get_file_path(char **command, char **path);

#endif