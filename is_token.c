/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 09:05:28 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/30 09:09:54 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	has_quote(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

int	recognize_op(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	else if (ft_strcmp(str, ">") == 0)
		return (2);
	else if (ft_strcmp(str, "<") == 0)
		return (3);
	else if (ft_strcmp(str, ">>") == 0)
		return (4);
	else if (ft_strcmp(str, "<<") == 0)
		return (3);
	else
		return (-1);
}

char	*ft_free(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
	{
		free (str1);
		str1 = NULL;
	}
	if (str2)
	{
		free (str2);
		str2 = NULL;
	}
	if (str3)
	{
		free (str3);
		str3 = NULL;
	}
	if (str4)
	{
		free (str4);
		str4 = NULL;
	}
	return (NULL);
}
