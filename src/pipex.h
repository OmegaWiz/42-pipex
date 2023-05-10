/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:15 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 09:42:02 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include<unistd.h>
# include<fcntl.h>
# include<stdio.h>
# include<sys/types.h>
# include<sys/wait.h>
# include<sys/errno.h>
# include<stdlib.h>
# include<errno.h>
# include "../lib/libft/libft.h"

typedef struct s_process
{
	int		pipe[2];
	int		pid;
	char	**cmd;
}				t_process;

typedef struct s_pipex
{
	int			pcnt;
	char		*filename[2];
	char		**envp;
	t_process	*proc;
	t_list		*openfd;
}				t_pipex;

// pipex_init.c
void	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
int		argc_handler(int argc, char **argv);

// pipex_execute.c
void	pipex_exec(t_pipex *pipex, int pnum);

void	pipex_free(t_pipex *pipex);
void	pipex_error(t_pipex *pipex, char *msg, int err, int exitno);

#endif
