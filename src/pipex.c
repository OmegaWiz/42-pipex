/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:10:03 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 08:27:30 by kkaiyawo         ###   ########.fr       */
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
	while (i < pipex.proc)
	{
		fs.process[i].pid = fork();
		if (fs.process[i].pid == -1)
			pipex_error(&pipex, "fork", errno, 1);
		else if (fs.process[i].pid == 0)
			pipex_exec(&pipex, i);
		else
			i++;
	}
	pipex_free(&pipex);
	i = 0;
	while (i < pipex.proc)
		waitpid(fs.process[i++].pid, &status, 0);
	return (WEXITSTATUS(status));
}
