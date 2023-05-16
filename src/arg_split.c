/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:17:10 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/16 08:36:41 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**arg_split(char *arg, t_pipex *pipex)
{
	char	**cmd;
	int		cnt;
	int		i;
	int		k;

	cnt = arg_count(arg);
	cmd = malloc(sizeof(char *) * (cnt + 1));
	if (!cmd)
		pipex_error(pipex, "cmd: arg_split()", ALLOC_ERROR, errno);
	i = 0;
	k = 0;
	while (k < cnt)
	{
		cmd[k] = arg_newsplit(arg, &i, pipex);
		if (!cmd[k])
		{
			ft_cleararr(cmd);
			pipex_error(pipex, "cmd: arg_split()", ALLOC_ERROR, errno);
		}
		k++;
	}
	cmd[k] = NULL;
	return (cmd);
}

int	arg_count(char *arg)
{
	int	i[4];

	set_zero(i, i + 3);
	while (arg[i[0]])
	{
		while (arg[i[0]] && is_ws_or_brac(arg[i[0]], 1))
			i[0]++;
		if (!arg[i[0]])
			break ;
		i[1] = i[0];
		while (arg[i[0]] && !is_ws_or_brac(arg[i[0]], 1))
		{
			if (is_ws_or_brac(arg[i[0]], 0))
			{
				i[2] = i[0]++;
				while (arg[i[0]] && arg[i[0]] != arg[i[2]])
					i[0]++;
			}
			i[0]++;
		}
		i[3]++;
	}
	return (i[3]);
}

char	*arg_newsplit(char *arg, int *i, t_pipex *pipex)
{
	int		j;
	int		k;

	while (arg[*i] && is_ws_or_brac(arg[*i], 1))
		(*i)++;
	j = *i;
	while (arg[*i] && !is_ws_or_brac(arg[*i], 1))
	{
		if (is_ws_or_brac(arg[*i], 0))
		{
			k = (*i)++;
			while (arg[*i] && arg[*i] != arg[k])
				(*i)++;
		}
		(*i)++;
	}
	return (arg_trunc_quote(arg, j, *i, pipex));
}

char	*arg_trunc_quote(char *arg, int j, int i, t_pipex *pipex)
{
	char	*tmp;
	int		k[2];

	tmp = (char *) pipex_malloc(sizeof(char) * (i - j + 1), "arg_trunc", pipex);
	k[0] = 0;
	while (j + k[0] < i)
	{
		if (!is_ws_or_brac(arg[j + k[0]], 0))
			tmp[k[0]] = arg[j + k[0]];
		if (!is_ws_or_brac(arg[j + k[0]], 0))
			k[0]++;
		else
		{
			k[1] = k[0] + j++;
			while (arg[j + k[0]] && arg[j + k[0]] != arg[k[1]] && j + k[0] < i)
			{
				tmp[k[0]] = arg[k[0] + j];
				k[0]++;
			}
			j++;
		}
	}
	tmp[k[0]] = '\0';
	return (tmp);
}

int	is_ws_or_brac(char c, int is_ws)
{
	if (is_ws)
		return (c == ' ' || c == '\t');
	else
		return (c == '\"' || c == '\'');
}
