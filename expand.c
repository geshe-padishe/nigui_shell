/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 06:42:27 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/13 07:02:40 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

char	*trio_merge(char *before, char *value, char *after)
{
	char	*expanded;
	size_t	len;

	len = ft_strlen(before) + ft_strlen(value) + ft_strlen(after);
	expanded = malloc(sizeof(char) * (len + 1));
	if (!expanded)
		return (free(expanded), NULL);
	expanded[0] = '\0';
	ft_strlcat(expanded, before, ft_strlen(before) +1);
	ft_strlcat(expanded, value, ft_strlen(before) + ft_strlen(value) + 1);
	ft_strlcat(expanded, after, len + 1);
	return (expanded);
}

char	*trio_split(char *str, int i_len[2], char *exit, t_dynarray *darr)
{
	char	*before;
	char	*name;
	char	*after;
	char	*value;
	char	*new;

	if (i_len[0] == 1)
	{
		str[i_len[1]] *= -1;
		return (str);
	}
	before = ft_substr(str, 0, i_len[1]);
	name = ft_substr(str, i_len[1], i_len[0]);
	after = ft_substr(str, i_len[1] + i_len[0], ft_strlen(str) - (i_len[0] + i_len[0]));
	value = ft_getenvval(name, darr, 1, 0);
	printf("EXPANDING VALUE\n");
	printf("VALUE = %s\n", value);
	if (!value)
		value = "";
	if (!ft_strcmp(name, "$?"))
		new = trio_merge(before, exit, after);
	else
		new = trio_merge(before, value, after);
	ft_free(before, name, after, str);
	if (!new)
		return (NULL);
	return (new);
}

char	*my_expand(char *str, int ext, t_dynarray *darr)
{
	int		i_len[2];
	char	*expanded;
	char	*exit;

	i_len[0] = -1;
	expanded = NULL;
	exit = ft_itoa(ext);
	if (!str || !exit)
		return (free(exit), NULL);
	while (str[++i_len[0]])
	{
		if (str[i_len[0]] == '$')
		{
			i_len[1] = var_name_len(&str[i_len[0]]);
			expanded = trio_split(str, i_len, exit, darr);
			while (find_dollar(expanded))
				expanded = my_expand(expanded, ext, darr);
			break ;
		}
	}
	free(exit);
	if (expanded)
		return (expanded);
	return (str);
}