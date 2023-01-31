/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:26:57 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 21:48:13 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

// 	*singleton()
// {
// 	static
// }

char	*limitertofile(char *line, char *limiter, char *filename)
{
	char	*repl;
	char	*before;
	char	*after;
	int		pos;

	pos = ft_strnstr(has_heredoc(line), limiter,
			ft_strlen(has_heredoc(line))) - line;
	before = ft_substr(line, 0, pos);
	after = ft_strnstr(has_heredoc(line), limiter,
			ft_strlen(has_heredoc(line))) + ft_strlen(limiter);
	repl = trio_merge(before, filename, after);
	ft_free(before, limiter, NULL, NULL);
	return (repl);
}

void	hd_exp(char *limiter, char *file)
{
	char		*line;
	int			fd;
	int			diff;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (free(file), perror("open"));
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	ft_free(line, file, 0, 0);
	close(fd);
	exit(0);
}

char	*ft_exec_heredoc(char *limiter, char *file)
{
	int		pid;
	char	*done;

	pid = fork();
	done = NULL;
	if (pid == 0)
		hd_exp(limiter, file);
	waitpid(pid, &g_vrac.status, 0);
	if (WIFEXITED(g_vrac.status))
		g_vrac.status = WEXITSTATUS(g_vrac.status);
	return (done);
}

char	*heredoc(char *line)
{
	char	*here;
	char	*limiter;
	char	*file;
	char	*repl;

	here = has_heredoc(line);
	file = namefile();
	if (!file)
		return (NULL);
	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	if (!here)
		return (line);
	limiter = find_limiter(here);
	if (!ft_strncmp(limiter, "/tmp/file", 9))
		limiter = new_limiter(line, limiter);
	if (!limiter)
		return (line);
	neg_quotes(limiter);
	if (act_has_quote(limiter))
		limiter = dup_quote(limiter);
	ft_exec_heredoc(limiter, file);
	repl = limitertofile(line, limiter, file);
	return (repl);
}

char	*mult_heredoc(char *line)
{
	char	*last;
	char	*tmp;
	int		nb;

	tmp = has_heredoc(line);
	last = line;
	nb = 0;
	while (tmp)
	{
		tmp = has_heredoc(tmp);
		nb++;
	}
	tmp = NULL;
	while (nb--)
	{
		tmp = last;
		last = heredoc(last);
		printf("last is %s\n", last);
		if (tmp != last && nb - 1)
			free(tmp);
	}
	return (last);
}
