/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 06:16:45 by hkhater           #+#    #+#             */
/*   Updated: 2023/02/01 06:16:59 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

int	init_my_expand(int *i_len, char **expanded, int ext, char **exit)
{
	i_len[0] = -1;
	(*expanded) = NULL;
	(*exit) = ft_itoa(ext);
	return (1);
}

int	init_parse(char **exp, char **hd, int *upd)
{
	*upd = 1;
	(*hd) = NULL;
	(*exp) = NULL;
	return (1);
}

int	open_heredoc_file(int *fd, char *file, char **limiter, int *qu)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	*qu = act_has_quote(*limiter);
	if (qu)
	{
		neg_quotes(*limiter);
		*limiter = dup_quote(*limiter);
	}
	return (1);
}

int	manage_expand_in_heredoc(char **line, int ext, t_dynarray *darr)
{
	(*line) = my_expand(*line, ext, darr);
	if ((*line)[0] == '$')
		(*line) = my_expand(*line, ext, darr);
	return (1);
}

int	write_user_input(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}
