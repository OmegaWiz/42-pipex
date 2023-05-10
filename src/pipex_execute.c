/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:47:54 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 10:55:54 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	Execute the command in the child process
/* TODO
 * 3. check if it is the first process
 * 3a. if proc==0, check if the infile is readable
 * 3aa. if the infile is readable, open the file and dup2 it to stdin
 * 3aX. if the infile is not readable, exit with status 2
 * 3b. if proc!=0, dup2 the previous pipe to stdin (write end)
 * 4. check if it is the last process
 * 4a. if proc==pipex->proc-1, check if the file is writable
 * 4aa. if the file is writable, open the file and dup2 it to stdout
 * 4aX. if the file is not writable, exit with status 2
 * 4b. if proc!=pipex->proc-1, dup2 the current pipe to stdout (read end)
 * 5. close the pipe and all files, leaving only STDIN and STDOUT open
 * 6. execve the command
*/
void	pipex_exec(t_pipex *pipex, int pnum)
{
	int	fd[2]

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
	fd[1] = pipex->proc[pnum].pipe[1];
	if (pnum == pipex->pcnt - 1)
	{
		file_acccess(pipex->filename[1], W_OK, pipex);
		fd[1] = open(pipex->filename[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd[1] == -1)
			pipex_error(pipex, "open", errno, 1
		ft_lstadd_back(&pipex->openfd, ft_lstnew(&fd));
	}
	dup2stdio_close(fd, pipex);
	execve(pipex->proc[pnum].cmd[0], pipex->proc[pnum].cmd, pipex->envp);
}

//	Find the executable and check its permission
void	find_executable(t_pipex *pipex, t_process *proc)
{
	int		i;
	char	*newpath;

	if (!ft_strchr(proc->cmd[0], '/'))
	{
		i = -1;
		newpath = proc->cmd[0];
		proc->cmd[0] = NULL;
		while (pipex->path[++i] && !proc->cmd[0])
		{
			newpath = ft_strprepend(newpath, pipex->path[i]);
			if (access(proc->cmd[0], F_OK) == 0)
				proc->cmd[0] = newpath;
		}
		if (!proc->cmd[0])
			pipex_error(pipex, proc->cmd[0], 127, 1);
	}
	file_access(proc->cmd[0], X_OK, pipex);
}

void	file_access(char *filename, int accmode, t_pipex *pipex)
{
	int	fd;

	if (accmode == W_OK && access(filename, F_OK) == -1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
		ft_lstdelone(&tmp, free);
	}
}
