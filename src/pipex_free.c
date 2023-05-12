/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:12:13 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/11 17:25:36 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_free(t_pipex *pipex)
{
	int		i;

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
	openfd_free(pipex->openfd);
}

void	openfd_free(t_list *openfd)
{
	t_list	*tmp;

	while (openfd)
	{
		tmp = openfd;
		openfd = openfd->next;
		if (tmp->content)
			close(*(int *) tmp->content);
		free(tmp);
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
