/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niki_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:01:52 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/28 21:28:35 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char const *s, int c)
{
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			while (i + j < len && (needle[j] == haystack[i + j]))
			{
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	ft_close_free(int **pipefd, int nb_pipes, t_lst *lst, t_dynarray *darr)
{
	if (lst)
		free_lst(lst);
	if (ft_close_pipes(pipefd, nb_pipes))
		return (free_pipe_array(pipefd, nb_pipes),
			ft_free_all(darr, lst, pipefd, nb_pipes), 1);
	free_pipe_array(pipefd, nb_pipes);
	ft_free_all(darr, lst, pipefd, nb_pipes);
	return (0);
}

int	malloc_envpi(char **envpi, int i)
{
	*envpi = malloc(i);
	if (!*envpi)
		return (0);
	return (1);
}

void	prep_tout(t_tout *tout)
{
	tout->ret_built = -3;
	tout->b_or_w = 0;
	tout->std_out = 0;
	tout->std_in = 0;
	tout->out_ch = 0;
	tout->in_ch = 0;
}
