/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 08:29:12 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/15 14:23:00 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	null_init(t_pipex *pipex)
{
	pipex->pcnt = 0;
	pipex->is_heredoc = 0;
	pipex->filename[0] = NULL;
	pipex->filename[1] = NULL;
	pipex->envp = NULL;
	pipex->path = NULL;
	pipex->proc = NULL;
}

//	t_pipex initialization
/* TODO
 * B. filename[] heredoc support
*/
void	pipex_init(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	i;

	null_init(pipex);
	pipex->pcnt = argc_handler(argc, argv, pipex);
	pipex->filename[0] = argv[1];
	pipex->filename[1] = argv[argc - 1];
	pipex->envp = envp;
	pipex->path = get_path_from_envp(pipex, envp);
	pipex->proc = malloc(sizeof(t_process) * pipex->pcnt);
	if (!pipex->proc)
		pipex_error(pipex, "pipex->proc: pipex_init()", ALLOC_ERROR, errno);
	i = pipex->pcnt - 1;
	while (--i >= 0)
	{
		if (pipe(pipex->proc[i].pipe) == -1)
			pipex_error(pipex, "pipe: pipex_init()", PIPE_ERROR, errno);
	}
	while (++i < pipex->pcnt)
	{
		pipex->proc[i].cmd = arg_split(argv[i + pipex->is_heredoc + 2], pipex);
		if (!pipex->proc[i].cmd)
			pipex_error(pipex, "proc[i].cmd: pipex_init()", ALLOC_ERROR, 1);
	}
}

//	check if argc is valid and return number of process
/* TODO
 * B. multiple pipes support
 * B. heredoc support
*/
int	argc_handler(int argc, char **argv, t_pipex *pipex)
{
	if (!BONUS)
	{
		if (argc != 5)
		{
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
			exit(1);
		}
		return (2);
	}
	else
	{
		if (argc < 5)
		{
			ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
			exit(1);
		}
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			pipex->is_heredoc = 1;
			return (argc - 4);
		}
		return (argc - 3);
	}
}

char	**get_path_from_envp(t_pipex *pipex, char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				pipex_error(pipex, "path: gpf_envp()", ALLOC_ERROR, errno);
			return (path);
		}
		i++;
	}
	return (NULL);
}
