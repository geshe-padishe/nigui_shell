/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:44:23 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/25 23:45:11 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

char	*find_var_name(char *str)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	len = var_name_len(str);
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		return (NULL);
	while (len--)
	{
		name[i] = str[i + 1];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*find_var_value(char *str)
{
	char	*name;
	char	*value;

	name = find_var_name(str);
	value = getenv(name);
	free(name);
	return (value);
}

int	var_name_len(char *str)
{
	int		i;

	i = 0;
	str++;
	if (*str == '?')
		return (1);
	if (!str)
		return (0);
	while (str[i] && is_alnumund(str[i]))
	{
		if (ft_isdigit(str[0]))
		{
			while (ft_isdigit(str[i]))
				i++;
			break ;
		}
		i++;
	}
	return (i);
}

char	*protect_content(char *str, int rev)
{
	int	c;
	int	len;

	c = *str++;
	while (*str && *str != c)
	{
		if (c == '"' && *str == '$')
		{
			len = var_name_len(str++);
			if (len == 0)
				*str *= -1;
			while (len--)
				str++;
		}
		if (*str != c && rev == 0)
			*str *= -1;
		if (*str != c && rev == 1)
		{
			if (*str < 0)
				*str *= -1;
		}
		if (*str && *str != c)
			str++;
	}
	return (str);
}

char	*dup_quote(char *s)
{
	int		i;
	int		j;
	char	*dup;
	size_t	size;

	i = 0;
	j = 0;
	printf("dup_quote\n");
	size = unquote_len(s);
	dup = malloc(sizeof(char) * (size + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		if (s[i] < 0)
			i++;
		else
			dup[j++] = s[i++];
	}
	dup[j] = '\0';
	free(s);
	return (dup);
}
