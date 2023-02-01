/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:26:57 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 21:21:37 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*limitertofile(char *line, char *limiter, char *filename)
{
	char	*repl;
	char	*before;
	char	*after;
	char	*point;
	int		pos;

	point = has_heredoc(line);
	pos = ft_strnstr(point, limiter, ft_strlen(point)) - line;
	before = ft_substr(line, 0, pos);
	if (!ft_strncmp(line, "/tmp/file", 9))
		free (line);
	after = ft_strnstr(point, limiter, ft_strlen(point)) + ft_strlen(limiter);
	repl = trio_merge(before, filename, after);
	ft_free(before, 0, NULL, NULL);
	return (repl);
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

static void	hd_exp(char *limiter, char *file, int ext, t_dynarray *darr)
{
	char		*line;
	int			fd;
	int			qu;

	open_heredoc_file(&fd, file, &limiter, &qu);
	if (fd == -1)
		return (free(file), perror("open"), exit(1));
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &here_sig);
		line = readline("heredoc>");
		if (!line)
			put_err("minishell: warning: end-of-file (wanted `eof')\n");
		if (!line || !ft_strcmp(line, limiter))
			break ;
		if (!qu)
			manage_expand_in_heredoc(&line, ext, darr);
		write_user_input(fd, line);
	}
	ft_free_env(g_vrac.darr);
	ft_free(line, file, limiter, 0);
	close(fd);
	exit(0);
}

static void	ft_exec_heredoc(char *limiter, char *file,
	int ext, t_dynarray *darr)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		hd_exp(limiter, file, ext, darr);
	waitpid(pid, &g_vrac.status, 0);
	if (WIFEXITED(g_vrac.status))
		g_vrac.status = WEXITSTATUS(g_vrac.status);
	return ;
}

static char	*heredoc(char *line, int ext, t_dynarray *darr)
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
	if (!limiter)
		return (line);
	ft_exec_heredoc(limiter, file, ext, darr);
	repl = limitertofile(line, limiter, file);
	return (ft_free(file, limiter, 0, 0), repl);
}

char	*mult_heredoc(char *line, int ext, t_dynarray *darr)
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
		last = heredoc(last, ext, darr);
		if (tmp != line && nb != -1)
			free(tmp);
	}
	return (last);
}
