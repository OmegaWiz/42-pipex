/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:10:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/11 09:49:09 by kkaiyawo         ###   ########.fr       */
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
			pipex_error(&pipex, "fork", errno, errno);
		else if (pipex.proc[i].pid == 0)
			pipex_exec(&pipex, &pipex.proc[i], i);
		else
			i++;
	}
	pipex_free(&pipex);
	i = 0;
	while (i < pipex.pcnt)
		waitpid(pipex.proc[i++].pid, &status, 0);
	return (WEXITSTATUS(status));
}
