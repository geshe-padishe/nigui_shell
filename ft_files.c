/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:24 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 07:30:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_create2(char *path2, int token, int apnd_or_not)
{
	int	fd;

	if (access(path2, F_OK))
	{
		if (token == 3)
			return (free(path2), perror("access"), -1);
		fd = open(path2, O_RDWR | O_CREAT | O_APPEND * apnd_or_not, S_IRWXU);
		if (fd == -1)
			return (free(path2), perror("open"), -1);
	}
	else if (!access(path2, R_OK | W_OK))
	{
		fd = open(path2, O_RDWR | O_APPEND * apnd_or_not);
		if (fd == -1)
			return (free(path2), perror("open"), -1);
	}
	else
		return (free(path2), perror("access"), -1);
	return (free(path2), fd);
}

int	ft_open_create(char *filename, bool apnd_or_not, int token)
{
	char	*path;
	char	*path2;
	char	buffer[10000];

	if (!getcwd(buffer, 10000))
		return (perror("getcwd"), -1);
	path = ft_strjoin(buffer, "/");
	if (!path)
		return (perror("malloc"), -1);
	path2 = ft_strjoin(path, filename);
	if (!path2)
		return (perror("malloc"), -1);
	free(path);
	return (ft_open_create2(path2, token, apnd_or_not));
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
