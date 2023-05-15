/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:36:00 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/15 09:20:30 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_error(t_pipex *pipex, char *msg, enum e_error err, int errnum)
{
	ft_putstr_fd("bash: ", 2);
	if (err == CMD_ERROR || err == FILE_ERROR || err == ACCESS_ERROR)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err == CMD_ERROR)
		ft_putendl_fd("command not found", 2);
	else
		ft_putendl_fd(strerror(errnum), 2);
	file_free(pipex);
	pipex_free(pipex);
	exit(errnum);
}

void	ft_strerror(t_pipex *pipex, char *msg, enum e_error err, int exitno)
{
	pipex_free(pipex);
	ft_putstr_fd("bash: ", 2);
	if (err == CMD_ERROR || err == FILE_ERROR || err == ACCESS_ERROR)
		ft_putstr_fd(msg, 2);
	if (err == ARGC_ERROR)
		ft_putstr_fd("Invalid number of arguments\n", 2);
	if (err == PIPE_ERROR)
		ft_putstr_fd("pipe failed\n", 2); //check
	if (err == FORK_ERROR)
		ft_putstr_fd("fork failed\n", 2); //check
	if (err == CMD_ERROR)
		ft_putstr_fd(": command not found\n", 2);
	if (err == FILE_ERROR)
		ft_putstr_fd(": No such file or directory\n", 2);
	if (err == ACCESS_ERROR)
		ft_putstr_fd(": Permission denied\n", 2);
	if (err == OPEN_ERROR)
		ft_putstr_fd("open failed\n", 2); //check
	if (err == CLOSE_ERROR)
		ft_putstr_fd("close failed\n", 2); //check
	if (err == EXEC_ERROR)
		ft_putstr_fd("execve failed\n", 2); //check
	if (err == ALLOC_ERROR)
		ft_putstr_fd("Cannot allocate memory\n", 2); //check
	exit(exitno);
}
