/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:26:57 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 16:30:58 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

// 	*singleton()
// {
// 	static
// }
static void	ft_child_sig(int signal)
{
	if (signal == SIGINT)
		printf("\n");
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

char	*mult_heredoc(char *line, int ext, t_dynarray *darr)
{
	char	*last;
	char	*tmp;
	int		nb;
	int		i;
	
	i = 0;	
	tmp = has_heredoc(line);
	last = line;
	nb = 0;
	signal(SIGQUIT, &ft_child_sig);
	signal(SIGINT, &ft_child_sig);
	if (!tmp)
		return (exit(0), line);
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
		if (tmp != last && i)
			free(tmp);
		--i;
	}
	exit (0);
	return (last);
}

char	*ft_exec_heredoc(char *line, int ext, t_dynarray *darr)
{
	int		pid;
	char	*done;

	printf("FORK HEREDOC\n");
	pid = fork();
	done = NULL;
	if (pid == 0)
		done = mult_heredoc(line, ext, darr);
	waitpid(pid, &g_vrac.status, 0);
	if (WIFEXITED(g_vrac.status))
		g_vrac.status = WEXITSTATUS(g_vrac.status);
	if (done == NULL)
		return (line);
	return (done);
}
