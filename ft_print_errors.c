/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:03:25 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 21:52:17 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dir_error(char *path_name)
{
	write(2, "bash: ", 6);
	write(2, path_name, ft_strlen(path_name));
	write(2, ": Is a directory\n", 17);
}

void	ft_cmd_error(char *path_name)
{
	write(2, "bash: ", 6);
	write(2, path_name, ft_strlen(path_name));
	write(2, ": command not found\n", 20);
}

void	ft_perm_error(char *path_name)
{
	write(2, "bash: ", 6);
	write(2, path_name, ft_strlen(path_name));
	write(2, ": Permission denied\n", 20);
}

void	ft_nofile_error(char *path_name)
{
	write(2, "bash: ", 6);
	write(2, path_name, ft_strlen(path_name));
	write(2, ": No such file or directory\n", 28);
}

void	num_arg(char **args)
{
	put_err("bash: exit: ");
	put_err(args[1]);
	put_err(": numeric argument required\n");
	free(args);
}
