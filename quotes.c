/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <ngenadie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 23:44:23 by hkhater           #+#    #+#             */
/*   Updated: 2023/02/01 03:25:47 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

int	var_name_len(char *str)
{
	int		i;

	i = 0;
	str++;
	if (!str)
		return (0);
	if (*str == '?')
		return (1);
	while (str[i] && is_alnumund(str[i]))
	{
		if (ft_isdigit(str[0]))
			return (1);
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
		while (c == '"' && *str == '$')
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

void	rm_quote(t_lst *lst)
{
	char	*old;

	if (!lst)
		return ;
	while (lst && lst->str)
	{
		if (lst->token == 0)
		{
			old = lst->str;
			if (has_quote(old))
				lst->str = dup_quote(old);
		}
		lst = lst->next;
	}
}
