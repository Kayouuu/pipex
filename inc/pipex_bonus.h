/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:01:42 by psaulnie          #+#    #+#             */
/*   Updated: 2022/01/22 11:33:11 by psaulnie         ###   ########.fr       */
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
	char	*limiter;
	char	*final_path;
	int		old_stdout;
	int		start;
	int		end;
}	t_data;

/*	MAIN_BONUS.C	*/

void	error(int argc, char *argv[]);

/*	DESTROY.C	*/

void	destroy(t_data *data, int has_error, char *error_msg);
void	free_tab(char **tab);

/*	FORKING_BONUS.C	*/

void	process_wait(t_data *data);
void	launch(int cmd_num, t_data *data);
void	forking(t_data *data);
void	pipeline(t_data *data, int i);

/*	PROCESS_BONUS.C	*/

int		forking_here_doc(t_data *data);
int		execute_here_doc(t_data *data, int i);
int		process(t_data *data, int i);

/*	HERE_DOC_BONUS.C	*/

int		reading(int fd[2]);
void	here_doc_launch(t_data *data, int cmd_nbr);
void	here_doc(int argc, char *argv[], char **envp);

/*	PATH_BONUS.C	*/

char	**get_path(t_data *data, char **envp);
char	*get_file_path(t_data *data, int cmd_num);

#endif