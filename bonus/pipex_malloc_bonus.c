/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_malloc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:24:47 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 08:52:43 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	*pipex_malloc(size_t size, char *func, t_pipex *pipex)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		pipex_error(pipex, func, ALLOC_ERROR, errno);
	return (ptr);
}

void	set_zero(int *i, int *j)
{
	*i = 0;
	*j = 0;
}
