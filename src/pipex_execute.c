/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:47:54 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 10:18:44 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	Execute the command in the child process
/* TODO
 * 3. check if it is the first process
 * 3a. if proc==0, check if the file is readable
 * 3aa. if the file is readable, open the file and dup2 it to stdin
 * 3aX. if the file is not readable, exit with status 2
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
	find_executable(pipex, &pipex->proc[pnum]);
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
	if (access(proc->cmd[0], F_OK) == -1)
		pipex_error(pipex, proc->cmd[0], 127, 1);
	else if (access(proc->cmd[0], X_OK) == -1)
		pipex_error(pipex, proc->cmd[0], 126, 1);
}
