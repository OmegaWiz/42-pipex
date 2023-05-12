/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:09:15 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/12 16:19:29 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H
# include<unistd.h>
# include<fcntl.h>
# include<stdio.h>
# include<string.h>
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

# define BONUS 0

typedef struct s_process
{
	int		pipe[2];
	pid_t	pid;
	char	**cmd;
}				t_process;

typedef struct s_pipex
{
	int			pcnt;
	int			is_heredoc;
	char		*filename[2];
	char		**envp;
	char		**path;
	t_process	*proc;
	t_list		*openfd;
}				t_pipex;

enum e_error
{
	ARGC_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	CMD_ERROR,
	FILE_ERROR,
	ACCESS_ERROR,
	OPEN_ERROR,
	CLOSE_ERROR,
	EXEC_ERROR,
	ALLOC_ERROR,
};

// pipex_init.c
void	null_init(t_pipex *pipex);
void	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp);
int		argc_handler(int argc, char **argv, t_pipex *pipex);
char	**get_path_from_envp(t_pipex *pipex, char **envp);

// pipex_execute.c
void	pipex_exec(t_pipex *pipex, t_process *proc, int pnum);
void	find_executable(t_pipex *pipex, t_process *proc);
void	file_access(char *filename, int accmode, t_pipex *pipex);
void	dup2stdio_close(int fd[2], t_pipex *pipex);

// pipex_file.c
int		check_inpipe(t_process proc, int openside, t_pipex *pipex);

// pipex_free.c
void	pipex_free(t_pipex *pipex);
void	openfd_free(t_list *openfd);
void	ft_cleararr(char **arr);

// pipex_error.c
void	pipex_error(t_pipex *pipex, char *msg, enum e_error err, int errnum);

// arg_split.c
char	**arg_split(char *arg, t_pipex *pipex);
int		arg_count(char *arg, t_pipex *pipex);
char	*arg_newsplit(char *arg, int *i, t_pipex *pipex);
char	*arg_trunc_quote(char *arg, int j, int i, t_pipex *pipex);
int		is_ws_or_brac(char c, int is_ws);

// ft_strprepend.c
char	*ft_strprepend(char *s1, char *s2);

#endif
