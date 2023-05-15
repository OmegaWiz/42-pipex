/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:10:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/15 10:04:55 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		status;

	pipex_init(&pipex, argc, argv, envp);
	i = 0;
	while (i < pipex.pcnt)
	{
		pipex.proc[i].pid = fork();
		if (pipex.proc[i].pid == -1)
			pipex_error(&pipex, "fork: main()", FORK_ERROR, errno);
		else if (pipex.proc[i].pid == 0)
			pipex_exec(&pipex, i);
		else
			i++;
	}
	closepipe_main(&pipex);
	i = 0;
	while (i < pipex.pcnt)
	{
		waitpid(pipex.proc[i].pid, &status, 0);
		//dprintf(2, "process #%d returns %d\n", pipex.proc[i].pid, status);
		i++;
	}
	pipex_free(&pipex);
	return (WEXITSTATUS(status));
}

void	closepipe_main(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->pcnt - 1)
	{
		close(pipex->proc[i].pipe[0]);
		close(pipex->proc[i].pipe[1]);
	}
}
