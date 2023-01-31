/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:06:13 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/30 21:08:02 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "miniparsing.h"

char	*find_limiter(char *s)
{
	int		i;

	i = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s == '\0')
			return (NULL);
		if (is_operator(*s))
			return (NULL);
		while (*(s + i) != '\0' &&!is_space(*(s + i)) && !is_operator(*(s + i)))
			i++;
		return (ft_substr(s, 0, i));
	}
	return (NULL);
}

char	*has_heredoc(char *line)
{
	if (!line || ft_strlen(line) < 3)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<')
			return (line + 2);
		line++;
	}
	return (NULL);
}

int	act_has_quote(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (is_quote(*s))
			return (1);
		s++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '\0' || s2[i] == '\0') && i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
