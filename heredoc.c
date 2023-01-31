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

// 	*singleton()
// {
// 	static
// }

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

	pos = ft_strnstr(line, limiter, ft_strlen(line)) - line;
	before = ft_substr(line, 0, pos);
	after = ft_strnstr(line, limiter, ft_strlen(line)) + ft_strlen(limiter);
	repl = trio_merge(before, filename, after);
	ft_free(before, limiter, NULL, NULL);
	return (repl);
}

char	*namefile(void)
{
	static int	i = 0;
	char		*nb;
	char		*file;

	nb = ft_itoa(i++);
	file = trio_merge("/tmp/file", nb, "");
	free (nb);
	return (file);	
}

char	*hd_exp(char *limiter, int exp, int ext, t_dynarray *darr)
{
	char		*file;
	char		*line;
	int			fd;
	int			diff;

	file = namefile();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (perror("OPEN"), NULL);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &here_sig);
		line = readline("heredoc>");
		if (!line)
			break ;
		diff = ft_strcmp(line, limiter);
		if (diff == 0)
			break ;
		if (exp)
			line = my_expand(line, ext, darr);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (ft_free(line, 0, 0, 0), close(fd), file);
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

char	*heredoc(char *line, int ext, t_dynarray *darr)
{
	char	*here;
	char	*limiter;
	char	*file;
	char	*repl;

	here = has_heredoc(line);
	if (!here)
		return (line);
	limiter = find_limiter(here);
	if (!ft_strncmp(limiter, "/tmp/file", 9))
		limiter = new_limiter(line, limiter);
	if (!limiter)
		return (line);
	if (!act_has_quote(limiter))
		file = hd_exp(limiter, 1, ext, darr);
	else
		file = hd_exp(limiter, 0, ext, darr);
	repl = limitertofile(line, limiter, file);
	return (free(file), repl);
}
