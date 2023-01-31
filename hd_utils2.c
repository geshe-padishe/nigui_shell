/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 05:37:00 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 21:31:19 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_sig(int sig)
{
	if (sig == SIGINT)
		exit (1);
}

void	ft_child_sig(int sig)
{
	if (sig == SIGINT)
		printf("\n");
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

void	safe_free(char *line, char *str)
{
	if (str && str != line)
	{
		free(str);
		str = NULL;
	}
}
