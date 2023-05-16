/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:12:13 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 08:49:42 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->proc)
	{
		while (++i < pipex->pcnt)
		{
			if (pipex->proc[i].cmd)
				ft_cleararr(pipex->proc[i].cmd);
		}
		free(pipex->proc);
	}
	if (pipex->path)
		ft_cleararr(pipex->path);
}

void	file_free(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->proc)
	{
		while (++i < pipex->pcnt - 1)
		{
			close(pipex->proc[i].pipe[0]);
			close(pipex->proc[i].pipe[1]);
		}
	}
}

void	ft_cleararr(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return ;
	while (arr[++i])
	{
		if (arr[i])
			free(arr[i]);
	}
	if (arr)
		free(arr);
}
