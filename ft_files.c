#include "minishell.h"

int	ft_open_create(char *filename, bool apnd_or_not, int token)
{
	int		fd;
	char	*path;
	char	*path2;
	char	buffer[10000];

	path = ft_strjoin(getcwd(buffer, 10000), "/");
	path2 = ft_strjoin(path, filename);
	free(path);
	if (access(path2, F_OK))
	{
		if (token == 3)
			return (free(path2), dprintf(2, "File not found\n"), -1);
		fd = open(path2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
		if (fd == -1)
			return (free(path2), dprintf(2, "Cannot create file\n"), -1);
	}
	else if (!access(path2, R_OK | W_OK))
	{
		fd = open(path2, O_RDWR | O_APPEND * apnd_or_not);
		if (fd == -1)
			return (free(path2), dprintf(2, "Cannot Open File\n"), -1);
	}
	else
		return (free(path2), dprintf(2, "File permission denied\n"), -1);
	return (free(path2), fd);
}

int	ft_is_dir(char *path_name)
{
	struct stat	stats;

	if (stat(path_name, &stats))
		return (0);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}
