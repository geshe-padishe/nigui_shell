/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:00:57 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 22:10:30 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static
char	*ft_strchr(char const *s, int c)
{
	if (c == '\0')
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;
	char	*init_path;

	if (ft_strchr(bin, '/'))
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 5);
	else
		bin_path = malloc(ft_strlen(bin) + ft_len_bef_col(paths) + 4);
	if (bin_path == NULL)
		return ((char *)3);
	init_path = bin_path;
	ft_strncpy(paths, bin_path, ft_len_bef_col(paths) + 1);
	bin_path[ft_len_bef_col(paths) + 1] = '/';
	ft_strcpy(bin, bin_path + 2 + ft_len_bef_col(paths));
	if (paths[0] != '/')
		bin_path -= 1;
	return (init_path);
}

int	ft_len_bef_col(char *paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if (paths[i] == ':')
			return (i - 1);
		i++;
	}
	return (i - 1);
}

int	ft_launch_bin(char *bin, char **argv, char **envp)
{
	if (access(bin, F_OK))
		return (free(argv), ft_nofile_error(bin), 127);
	if (ft_is_dir(bin))
		return (free(argv), ft_dir_error(bin), 126);
	if (access(bin, X_OK))
		return (free(argv), ft_perm_error(bin), 126);
	if (execve(bin, argv, envp))
		return (free(argv), perror("execve"), 1);
	return (0);
}

int	ft_find_bin(char *bin, char *paths, char **argv, char **envp)
{
	char	*bin_path;

	if (!bin[0])
		return (write(2, "bash: : command not found\n", 26), 127);
	else if (ft_strchr(bin, '/'))
		return (ft_launch_bin(bin, argv, envp));
	while (paths && *paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == (char *)3)
			return (perror("ft_find_bin"), 1);
		if (!access(bin_path, F_OK))
			if (!ft_is_dir(bin_path))
				if (!access(bin_path, X_OK))
					if (execve(bin_path, argv, envp))
						return (perror("execve"),
							free(bin_path), 1);
		free(bin_path);
		paths += ft_len_bef_col(paths) + 1;
		if (*paths)
			paths += 1;
	}
	return (ft_cmd_error(bin), 127);
}

int	ft_handle_exec(t_tout *tout)
{
	char	**args;
	int		ret;

	ret = ft_builtins(tout);
	if (ret == -3)
	{
		args = ft_splitargs(find_bin_lst(tout->lst));
		if (!args)
			return (ft_free_all(tout->darr, tout->lst, tout->pipefd,
					tout->nb_pipes), exit(1), 1);
		ret = ft_find_bin(args[0], ft_getenvval("PATH", tout->darr,
					0, 0), args, tout->darr->list);
		return (free(args), ft_free_all(tout->darr, tout->lst, tout->pipefd,
				tout->nb_pipes), exit(ret), 1);
	}
	return (ft_free_all(tout->darr, tout->lst, tout->pipefd,
			tout->nb_pipes), exit(ret), 1);
}
