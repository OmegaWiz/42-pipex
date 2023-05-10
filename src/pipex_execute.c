/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:47:54 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 17:42:39 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	Execute the command in the child process
void	pipex_exec(t_pipex *pipex, t_process *proc, int pnum)
{
	int	fd[2];

	find_executable(pipex, &pipex->proc[pnum]);
	if (pnum == 0)
	{
		file_access(pipex->filename[0], R_OK, pipex);
		fd[0] = open(pipex->filename[0], O_RDONLY);
		if (fd[0] == -1)
			pipex_error(pipex, "open", errno, 1);
		ft_lstadd_back(&pipex->openfd, ft_lstnew(&fd));
	}
	else
		fd[0] = pipex->proc[pnum - 1].pipe[0];
	if (pnum == pipex->pcnt - 1)
	{
		file_access(pipex->filename[1], W_OK, pipex);
		fd[1] = open(pipex->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			pipex_error(pipex, "open", errno, 1);
		ft_lstadd_back(&pipex->openfd, ft_lstnew(&fd));
	}
	else
		fd[1] = pipex->proc[pnum].pipe[1];
	dup2stdio_close(fd, pipex);
	execve(pipex->proc[pnum].cmd[0], pipex->proc[pnum].cmd, pipex->envp);
}

//	Find the executable and check its permission
void	find_executable(t_pipex *pipex, t_process *proc)
{
	int		i;
	char	*newpath;
	int		b;

	if (!ft_strchr(proc->cmd[0], '/'))
	{
		i = -1;
		b = 0;
		newpath = NULL;
		while (pipex->path[++i] && !b)
		{
			newpath = ft_strprepend(proc->cmd[0], pipex->path[i]);
			if (access(newpath, X_OK) == 0)
			{
				free(proc->cmd[0]);
				proc->cmd[0] = newpath;
				b = 1;
				break;
			}
			free(newpath);
		}
		if (!b)
			pipex_error(pipex, proc->cmd[0], 127, 1);
	}
	file_access(proc->cmd[0], X_OK, pipex);
}

//	Check if the file is accessible
void	file_access(char *filename, int accmode, t_pipex *pipex)
{
	int	fd;

	if (accmode == W_OK && access(filename, F_OK) == -1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
			pipex_error(pipex, filename, 2, 1);
		fd = close(fd);
		if (fd == -1)
			pipex_error(pipex, filename, 2, 1);
	}
	if (access(filename, F_OK) == -1)
		pipex_error(pipex, filename, 2, 1);
	if (access(filename, accmode) == -1)
		pipex_error(pipex, filename, 2, 1);
}

//	Redirect the standard input and output to the pipe and close the open file
void	dup2stdio_close(int fd[2], t_pipex *pipex)
{
	t_list	*tmp;

	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	while (pipex->openfd)
	{
		close(*(int *) pipex->openfd->content);
		tmp = pipex->openfd;
		pipex->openfd = pipex->openfd->next;
		free(tmp);
	}
}
