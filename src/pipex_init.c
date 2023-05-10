/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:29:12 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 08:41:15 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	check if argc is valid and return number of process
/* TODO
 * B. multiple pipes support
 * B. heredoc support
*/
int		argc_handler(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(1);
	}
	return (2);
}

//	t_pipex initialization
/* TODO
 * 1. cmd split
 * B. filename[] heredoc support
*/
void	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	pipex->proc = argc_handler(argc, argv);
	pipex->filename[0] = argv[1];
	pipex->filename[1] = argv[argc - 1];
	pipex->envp = envp;
	pipex->process = malloc(sizeof(t_process) * pipex->proc);
	if (!pipex->proc)
		pipex_error(pipex, "malloc", errno, 1);
	i = pipex->proc - 1;
	while (--i >= 0)
	{
		if (pipe(pipex->process[i].pipe) == -1)
			pipex_error(pipex, "pipe", errno, 1);
		ft_lstadd_front(&pipex->openfd, ft_lstnew(pipex->process[i].pipe[0]));
		ft_lstadd_front(&pipex->openfd, ft_lstnew(pipex->process[i].pipe[1]));
	}
}
