/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:15 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 08:14:18 by kkaiyawo         ###   ########.fr       */
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
	int			proc;
	char		*filename[2];
	char		**envp;
	t_list		*openfd;
	t_process	*process;
}				t_pipex;

#endif
