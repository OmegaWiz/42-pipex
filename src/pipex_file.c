/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:01:38 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/12 16:19:55 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_inpipe(t_process proc, int openside, t_pipex *pipex)
{
	t_list	*ptr;

	ptr = pipex->openfd;
	while (ptr)
	{
		if (*(int *) ptr->content != proc.pipe[1 - openside])
			ptr = ptr->next;
		else
			break;
	}
	if (!ptr)
	{
		if (close(proc.pipe[1 - openside]) == -1)
			pipex_error(pipex, "close: check_inpipe()", CLOSE_ERROR, errno);
	}
	return (proc.pipe[openside]);
}
