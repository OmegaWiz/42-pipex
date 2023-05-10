/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:17:10 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/05/10 12:43:08 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**arg_split(char *arg, t_pipex *pipex)
{
	char	**cmd;
	int		cnt;
	int		i;
	int		k;

	cnt = arg_count(arg, pipex);
	cmd = malloc(sizeof(char *) * cnt + 1);
	i = 0;
	k = 0;
	while (k < cnt)
	{
		cmd[k] = arg_newsplit(arg, &i);
		if (!cmd[k])
		{
			// ft_cleararr(cmd, k);
			// pipex_error("Malloc failed");
		}
	}
	cmd[k] = NULL;
	return (cmd);
}

int	arg_count(char *arg, t_pipex *pipex)
{
	int	i;
	int	j;
	int	k;
	int	cnt;

	cnt = 0;
	i = -1;
	while (arg[++i])
	{
		while (arg[i] && is_ws_or_brac(arg[i], 1))
			i++;
		j = i;
		while (arg[i] && !is_ws_or_brac(arg[i], 1))
		{
			if (is_ws_or_brac(arg[i], 0))
			{
				k = i++;
				while (arg[i] && arg[i] != arg[k])
					i++;
			}
			i++;
		}
		cnt++;
	}
	return (cnt);
}

char	*arg_newsplit(char *arg, int *i)
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
			k = *i;
			while (arg[*i] && arg[*i] != arg[k])
				(*i)++;
		}
		(*i)++;
	}
	return (arg_trunc_quote(arg, j, *i));
}

char	*arg_trunc_quote(char *arg, int j, int i)
{
	char	*tmp;
	int		k;
	int		l;

	tmp = malloc(sizeof(char) * (i - j + 1));
	if (!tmp)
		pipex_error("Malloc failed");
	k = 0;
	while (j + k < i)
	{
		if (is_ws_or_brac(arg[j + k], 0))
		{
			l = k;
			j++;
			while (arg[j + k] && arg[j + k] != arg[l] && j + k < i)
				tmp[k++] = arg[j + k];
			j++;
		}
		else
			tmp[k++] = arg[j + k];
	}
	tmp[k] = '\0';
	return (tmp);
}

int	is_ws_or_brac(char c, int is_ws)
{
	if (is_ws)
		return (c == ' ' || c == '\t');
	else
		return (c == '\"' || c == '\'');
}
