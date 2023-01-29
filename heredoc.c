#include "miniparsing.h"

char	*has_heredoc(char *line)
{
	if (!line)
		return (NULL);
	while (*line && *(line + 2))
	{
		if (*line == '<' && *(line + 1) == '<' && !is_operator(*(line + 2)))
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
		while (line &&!is_space(*(line + len)) && !is_operator(*(line + len)))
			len++;
		return (ft_substr(line, 0, len));
	}
	return(NULL);
}

char	*hd_exp(char *limiter)
{
	char	*file;
	char	*line;
	int		fd;
	int		diff;

	file = "/tmp/file1";
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (1)
	{
		line = readline(">");
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
	char	*limiter;
	char	*file;

	here = has_heredoc(line);
	if (!here)
		return (line);
	limiter = find_limiter(here);
	file = hd_exp(limiter);
	return (file);
}
