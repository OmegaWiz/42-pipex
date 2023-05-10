/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:57:22 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 15:00:42 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// ft-strprepend needs to add '/' between s2 and s1
char	*ft_strprepend(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s2, ft_strlen(s2) + 1);
	ft_strlcat(str, "/", ft_strlen(s2) + 2);
	ft_strlcat(str, s1, ft_strlen(s1) + ft_strlen(s2) + 2);
	free(s1);
	return (str);
}
