#include "minishell.h"

char	*ft_check_bin_path(char *bin, char *paths)
{
	char	*bin_path;
	char	*init_path;

	if (paths[0] != '/')
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

int	ft_find_bin(char *bin, char *paths, char **argv, char **envp)
{
	char	*bin_path;

	if (!bin[0])
		return (free(argv), write(2, "bash: : command not found\n", 26), 127);
	else if (bin[0] == '.' || bin[0] == '/')
	{
		if (access(bin, F_OK))
			return (free(argv), ft_nofile_error(bin), 127);
		if (ft_is_dir(bin))
			return (free(argv), ft_dir_error(bin), 126);
		if (access(bin, X_OK))
			return (free(argv), ft_perm_error(bin), 126);
		if (execve(bin, argv, envp))
			return (free(argv), perror("execve"), 1); //FREE
	}
	while (*paths)
	{
		bin_path = ft_check_bin_path(bin, paths);
		if (bin_path == (char *)3)
			return (free(argv), perror("ft_find_bin"), 1);
		if (!access(bin_path, F_OK))
			if (!ft_is_dir(bin_path))
				if (!access(bin_path, X_OK))
					if (execve(bin_path, argv, envp))
						return (free(argv), perror("execve"), free(bin_path), 1); //FREE ALL
		free(bin_path);
		paths += ft_len_bef_col(paths) + 1;
		if (*paths)
			paths += 1;
	}
	return (free(argv), ft_cmd_error(bin), 127);
}

int	ft_handle_exec(t_lst *lst, t_dynarray *darr, int **pipefd, int nb_pipes)
{
	char	**args;
	int		ret;

	args = ft_splitargs(lst);
	if (!args)
		return (ft_free_all(darr, lst, pipefd, nb_pipes), exit(1), 1);
	ret = ft_builtins(lst, darr, pipefd, nb_pipes);
	if (ret == -3)
	{
		ret = ft_find_bin(args[0], ft_getenvval("PATH", darr,
			0, 1), args, darr->list);
		return (ft_free_all(darr, lst, pipefd, nb_pipes), exit(ret), 1);
	}
	return (ft_free_all(darr, lst, pipefd, nb_pipes), free(args), exit(ret), 1);
}
//
//int	ft_builtins_exec(t_lst *lst, t_dynarray *darr)
//{
//	char	**args;
//
//	args = ft_splitargs(lst);
//	if (!args)
//		return (perror("malloc"), 1);
//	if (!nk_strcmp(lst->str, "echo"))
//		return (ft_echo(args + 1), 1);
//	else if (!nk_strcmp(lst->str, "pwd"))
//		return (ft_pwd(args + 1), 1);
//	else if (!nk_strcmp(lst->str, "env"))
//		return (ft_dyn_env(darr, args + 1), 1);
//	else if (!nk_strcmp(lst->str, "cd"))
//		return (ft_cd(args + 1), 1);
//	else if (!nk_strcmp(lst->str, "export"))
//		return (ft_export(darr, args + 1), 1);
//	else if (!nk_strcmp(lst->str, "unset"))
//		return (ft_unset(darr, args + 1), 1);
//	else if (!nk_strcmp(lst->str, "exit"))
//		return (ft_exit(args + 1, darr), 1);
//	return (free(args), -3);
//}
