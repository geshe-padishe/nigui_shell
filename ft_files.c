/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:24 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/29 02:59:28 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_create2(char *path2, int token, int apnd_or_not)
{
	int	fd;

	(void)apnd_or_not;
	if (token == 2)
		fd = open(path2, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (token == 3)
		fd = open(path2, O_RDONLY);
	else if (token == 4)
		fd = open(path2, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open(path2, O_RDONLY);
	if (fd == -1)
		return (free(path2), perror("open"), -1);
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
