/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:45:32 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/28 02:01:56 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcpy(char *str, char *str2)
{
	int	i;

	i = 0;
	if (!str || !str2)
		return (1);
	while (str[i])
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (0);
}

int	nk_strcmp(char const *str, char const *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (-1);
		i++;
	}
	if (str[i] != str2[i])
		return (-1);
	return (0);
}

bool	ft_can_exp(char *str)
{
	int	i;

	i = 0;
	if (!(str[0] >= 'A' && str[0] <= 'Z')
		&& !(str[0] >= 'a' && str[0] <= 'z') && !(str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (i != 0 && str[i] == '=')
			return (1);
		if (!is_alnumund(str[i]))
			return (0);
		i++;
	}
	return (0);
}

int	ft_strncpy(char *str, char *str2, int n)
{
	int	i;

	i = 0;
	while (str[i] && i < n)
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (0);
}

char	*ft_strjoin(char *str, char *str2)
{
	char	*str3;

	if (!str || !str2)
		return (NULL);
	str3 = malloc(ft_strlen(str) + ft_strlen(str2) + 1);
	if (str3 == NULL)
		return (NULL);
	ft_strcpy(str, str3);
	ft_strcpy(str2, str3 + ft_strlen(str));
	str3[ft_strlen(str) + ft_strlen(str2)] = '\0';
	return (str3);
}
