/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:57:22 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 08:48:27 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ft-strprepend needs to add '/' between s2 and s1
char	*ft_strprepend(char *s1, char *s2, t_pipex *pipex)
{
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		pipex_error(pipex, "ft_strprepend()", ALLOC_ERROR, errno);
	ft_strlcpy(str, s2, ft_strlen(s2) + 1);
	ft_strlcat(str, "/", ft_strlen(s2) + 2);
	ft_strlcat(str, s1, ft_strlen(s1) + ft_strlen(s2) + 2);
	return (str);
}
