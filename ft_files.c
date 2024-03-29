/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:24 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/30 19:50:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_create2(char *path2, char *filename, int token)
{
	int	fd;

	if (token == 2)
		fd = open(path2, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (token == 3)
		fd = open(path2, O_RDONLY);
	else if (token == 4)
		fd = open(path2, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(path2, O_RDONLY);
	if (fd == -1)
		return (put_err("bash: "), put_err(filename), perror(" "), -1);
	return (fd);
}

int	ft_open_create(char *filename, bool apnd_or_not, int token)
{
	int		ret;
	char	*path;
	char	*path2;
	char	buffer[10000];

	(void)apnd_or_not;
	if (filename && filename[0] == '/')
		return (ft_open_create2(filename, filename, token));
	if (!getcwd(buffer, 10000))
		return (perror("getcwd"), -1);
	path = ft_strjoin(buffer, "/");
	if (!path)
		return (perror("malloc"), -1);
	path2 = ft_strjoin(path, filename);
	if (!path2)
		return (free(path), perror("malloc"), -1);
	free(path);
	ret = ft_open_create2(path2, filename, token);
	return (free(path2), ret);
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
