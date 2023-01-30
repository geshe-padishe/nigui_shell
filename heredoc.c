/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:26:57 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/30 16:29:15 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

void	here_sig(int sig)
{
	if (sig == SIGINT)
		exit (1);
}

char	*limitertofile(char *line, char *limiter, char *filename)
{
	char	*repl;
	char	*before;
	char	*after;
	int		pos;

	printf("strnstr is %s\n", ft_strnstr(line, limiter, ft_strlen(line)));
	pos = ft_strnstr(line, limiter, ft_strlen(line)) - line;
	printf("pos is %d\n", pos);
	before = ft_substr(line, 0, pos);
	printf("before: %s\n", before);
	after = ft_strnstr(line, limiter, ft_strlen(line)) + ft_strlen(limiter);
	printf("after: %s\n", after);
	repl = trio_merge(before, filename, after);
	printf("replaced: %s\n", repl);
	return (repl);
}

char	*has_heredoc(char *line)
{
	if (!line)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<')
			return (line + 2);
		line++;
	}
	return (NULL);
}

char	*find_limiter(char *line)
{
	int		len;

	len = 0;
	while (*line)
	{
		while (is_space(*line))
			line++;
		if (is_operator(*line))
			return (NULL);
		while (*(line + len) != '\0' &&!is_space(*(line + len)) && !is_operator(*(line + len)))
			len++;
		return (ft_substr(line, 0, len));
	}
	return (NULL);
}

char	*hd_exp(char *limiter)
{
	char	*file;
	char	*line;
	int		fd;
	int		diff;

	file = "/tmp/file2";
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (perror("OPEN"), NULL);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &here_sig);
		line = readline("heredoc>");
		diff = strcmp(line, limiter);
		if (diff == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	return (file);
}

char	*heredoc(char *line)
{
	char	*here;
	char	*tmp;
	char	*limiter;
	char	*file;
	int		nb;

	nb = -1;
	here = has_heredoc(line);
	tmp = line;
	if (!here)
		return (line);
	while (tmp)
	{
		tmp = has_heredoc(tmp);
		nb++;
	}
	limiter = find_limiter(here);
	file = hd_exp(limiter);
	printf("tmp file is %s\n", file);
	tmp = limitertofile(line, limiter, file);
	free(limiter);
	return (tmp);
}
