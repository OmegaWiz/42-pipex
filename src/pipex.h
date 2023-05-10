/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:15 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 11:02:33 by kkaiyawo         ###   ########.fr       */
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

# ifndef STDIN_FILENO
#  define STDIN_FILENO 0
# endif
# ifndef STDOUT_FILENO
#  define STDOUT_FILENO 1
# endif
# ifndef STDERR_FILENO
#  define STDERR_FILENO 2
# endif

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
	char		**path;
	t_process	*proc;
	t_list		*openfd;
}				t_pipex;

// pipex_init.c
void	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
int		argc_handler(int argc, char **argv);
char	**get_path_from_envp(t_pipex *pipex, char **envp);

// pipex_execute.c
void	pipex_exec(t_pipex *pipex, t_process *proc, int pnum);
void	find_executable(t_pipex *pipex, int pnum);
void	file_access(char *filename, int accmode, t_pipex *pipex);
void	dup2stdio_close(int fd[2], t_pipex *pipex);

void	pipex_free(t_pipex *pipex);
void	pipex_error(t_pipex *pipex, char *msg, int err, int exitno);

// ft-strprepend needs to add '/' between s2 and s1
char	*ft_strprepend(char *s1, char *s2);

#endif
