/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:23:14 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/28 01:23:15 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_dyn_env(char **envp, t_dynarray *darr)
{
	int		i;
	char	*str;
	char	*nul;

	i = 0;
	nul = NULL;
	while (envp[i])
		i++;
	if (init_dynarray(darr, i + 10, sizeof(char *)))
		return (-1);
	i = -1;
	while (envp[++i])
	{
		str = malloc(ft_strlen(envp[i]) + 1);
		if (!str)
			return (ft_free_bcwrd(darr, i - 1), -1);
		ft_strcpy(envp[i], str);
		if (push_dynarray(darr, &str, 1, 0))
			return (free(str), ft_free_bcwrd(darr, i - 1), -1);
	}
	if (push_dynarray(darr, &nul, 1, 0))
		return (-1);
	return (0);
}

int	ft_getenv_index(char **envp, uint64_t len, char *str, bool un_exp)
{
	uint64_t	i;
	int			cmp;

	i = 0;
	while (i < len && envp[i])
	{
		cmp = ft_envcmp(envp[i], str);
		if (cmp == -1)
			i++;
		else if (cmp == -2)
		{
			if (un_exp == 1)
				return (i);
			else
				return (-1);
		}
		else
			return (i);
	}
	return (-1);
}

int	ft_envcmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i] && str[i] != '=' && str2[i] != '=')
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	if (str[i] == '=' && str2[i] == '=')
		return (-2);
	else if (str2[i] == '\0' && str[i] == '=')
		return (0);
	return (-1);
}

char	*ft_getenvval(char *str, t_dynarray *darr,
		bool val_or_all, bool un_or_exp)
{
	int		i;
	int		index;
	char	**envp;

	i = 0;
	envp = darr->list;
	index = ft_getenv_index(envp, darr->nb_cells, str, un_or_exp);
	if (index == -1)
		return (NULL);
	while (val_or_all == 0 && envp[index][i] && envp[index][i] != '=')
		i++;
	return (&envp[index][i + 1 - val_or_all]);
}
