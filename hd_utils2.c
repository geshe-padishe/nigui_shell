/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:37:00 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 05:49:39 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_child_sig(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

char	*new_limiter(char *line, char *limiter)
{
	char	*new_lim;
	char	*cropped;
	char	*pos;

	pos = ft_strnstr(line, limiter, ft_strlen(line));
	cropped = has_heredoc(pos + ft_strlen(limiter));
	new_lim = find_limiter(cropped);
	while (!ft_strncmp(new_lim, "/tmp/file", 9))
		new_lim = new_limiter(line, new_lim);
	return (free(limiter), new_lim);
}

void	neg_quotes(char *s)
{
	char	c;

	if (!s)
		return ;
	while (*s)
	{
		if (is_quote(*s))
		{
			c = *s;
			*s++ *= -1;
			while (*s != c)
				s++;
			*s *= -1;
		}
		s++;
	}
}
