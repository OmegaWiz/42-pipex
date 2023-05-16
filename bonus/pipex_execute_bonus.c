/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:47:54 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 08:49:33 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	Execute the command in the child process
void	pipex_exec(t_pipex *pipex, int pnum)
{
	int	fd[2];

	if (pnum == pipex->pcnt - 1)
		file_access(pipex->filename[1], W_OK, pipex);
	if (pnum == 0)
	{
		file_access(pipex->filename[0], R_OK, pipex);
		fd[0] = open(pipex->filename[0], O_RDONLY);
		if (fd[0] == -1)
			pipex_error(pipex, "open: pipex_exec()", OPEN_ERROR, errno);
	}
	else
		fd[0] = pipex->proc[pnum - 1].pipe[0];
	if (pnum == pipex->pcnt - 1)
	{
		file_access(pipex->filename[1], W_OK, pipex);
		fd[1] = open(pipex->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			pipex_error(pipex, "open: pipex_exec()", OPEN_ERROR, errno);
	}
	else
		fd[1] = pipex->proc[pnum].pipe[1];
	find_executable(pipex, &pipex->proc[pnum]);
	dup2stdio_close(fd, pnum, pipex);
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
			newpath = ft_strprepend(proc->cmd[0], pipex->path[i], pipex);
			if (access(newpath, X_OK) == 0)
			{
				free(proc->cmd[0]);
				proc->cmd[0] = newpath;
				b = 1;
				break ;
			}
			free(newpath);
		}
		if (!b)
			pipex_error(pipex, proc->cmd[0], CMD_ERROR, 127);
	}
	file_access(proc->cmd[0], X_OK, pipex);
}

//	Check if the file is accessible
void	file_access(char *filename, int accmode, t_pipex *pipex)
{
	int	fd;

	if (accmode == W_OK && access(filename, F_OK) == -1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			pipex_error(pipex, "open: file_access()", OPEN_ERROR, errno);
		fd = close(fd);
		if (fd == -1)
			pipex_error(pipex, "close: file_access()", CLOSE_ERROR, errno);
	}
	if (accmode == X_OK && !ft_strchr(filename, '/'))
	{
		if (access(filename, F_OK) == -1)
			pipex_error(pipex, filename, CMD_ERROR, 127);
	}
	if (access(filename, F_OK) == -1)
		pipex_error(pipex, filename, FILE_ERROR, errno);
	else
	{
		if (access(filename, accmode) == -1)
			pipex_error(pipex, filename, ACCESS_ERROR, errno);
	}
}

//	Redirect the standard input and output to the pipe and close the open file
void	dup2stdio_close(int fd[2], int pnum, t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pcnt - 1)
	{
		if (i == pnum - 1)
		{
			if (pnum != 0)
				close_check(pipex->proc[i].pipe[1], pipex, pnum);
		}
		else if (i == pnum)
		{
			if (pnum != pipex->pcnt - 1)
				close_check(pipex->proc[i].pipe[0], pipex, pnum);
		}
		else
		{
			close_check(pipex->proc[i].pipe[0], pipex, pnum);
			close_check(pipex->proc[i].pipe[1], pipex, pnum);
		}
	}
	dup2(fd[0], STDIN_FILENO);
	close_check(fd[0], pipex, pnum);
	dup2(fd[1], STDOUT_FILENO);
	close_check(fd[1], pipex, pnum);
}

void	close_check(int fd, t_pipex *pipex, int pnum)
{
	(void) pnum;
	if (close(fd) == -1)
		pipex_error(pipex, "close: dup2stdio_close()", CLOSE_ERROR, errno);
}
