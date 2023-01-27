/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:01:57 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 21:24:40 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_save_fds(t_tout *tout, t_lst *lst, int alone)
{
	if (!alone)
		return (0);
	if ((lst->token == 2 || lst->token == 4) && !tout->out_ch)
	{
		tout->std_out = dup(STDOUT_FILENO);
		if (tout->std_out == -1)
			return (perror("dup"), -1);
		tout->out_ch = 1;
	}
	if ((lst->token == 3 || lst->token == 5) && !tout->in_ch)
	{
		tout->std_in = dup(STDIN_FILENO);
		if (tout->std_in == -1)
			return (perror("dup"), -1);
		tout->in_ch = 1;
	}
	return (0);
}

int	ft_handle_redirections(t_tout *tout, int alone)
{
	t_lst	*lst;

	lst = tout->lst;
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3 || lst->token == 4)
		{
			if (ft_save_fds(tout, lst, alone))
				return (-1);
			if (ft_open_dup(lst, lst->token, 0) == -1)
				return (-1);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_open_dup(t_lst *lst, int token, bool apnd_or_not)
{
	int	fd;

	fd = -1;
	if (!lst->next)
		return (put_err("ambigous redirect\n"), -1);
	if (token == 2 || token == 4)
	{
		if (token == 4)
			apnd_or_not = 1;
		fd = ft_open_create(lst->next->str, apnd_or_not, token);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), perror("dup2"), -1);
	}
	else
	{
		fd = ft_open_create(lst->next->str, 0, token);
		if (fd == -1)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), perror("dup2"), -1);
	}
	return (fd);
}

int	ft_rewind_fds(t_tout *tout)
{
	if (tout->in_ch)
	{
		close(STDIN_FILENO);
		if (dup2(tout->std_in, STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
	}
	if (tout->out_ch)
	{
		close(STDOUT_FILENO);
		if (dup2(tout->std_out, STDOUT_FILENO) == -1)
			return (perror("dup2"), -1);
	}
	return (0);
}
