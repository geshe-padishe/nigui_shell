/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:00:51 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/30 16:29:49 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (!nb_pipes)
		return (0);
	if (pipes_left != nb_pipes)
	{
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
		if (*fd_in == -1)
			return (perror("dup2"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
	}
	if (pipes_left != 0)
	{
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (perror("dup2"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
	}
	return (ft_close_pipes(pipefd, nb_pipes), 0);
}

t_lst	*find_bin_lst(t_lst *lst)
{
	while (lst)
	{
		if (lst->token == 1)
			return (NULL);
		if (lst && lst->token == 0)
			return (lst);
		if (lst->token >= 2 && lst->token <= 5)
			lst = lst->next;
		lst = lst->next;
	}
	return (NULL);
}

int	child_routine(t_tout *tout)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_handle_pipe(tout->pipefd, tout->pipes_left,
			tout->nb_pipes, &tout->fd_in))
		return (ft_free_all(tout->darr, first_lst(tout->lst),
				tout->pipefd, tout->nb_pipes), exit(1), 1);
	if (ft_handle_redirections(tout, 0))
		return (ft_free_all(tout->darr, first_lst(tout->lst),
				tout->pipefd, tout->nb_pipes), exit(1), 1);
	if (ft_handle_exec(tout))
		return (ft_free_all(tout->darr, first_lst(tout->lst),
				tout->pipefd, tout->nb_pipes), exit(127), 1);
	exit(1);
	return (0);
}

int	launch_child(t_tout *tout)
{
	tout->i = 0;
	while (tout->lst && tout->lst->str)
	{
		prep_tout(tout);
		if (!tout->nb_pipes && ft_is_built(find_bin_lst(tout->lst)))
		{
			if (ft_have_redirs(tout->lst))
				if (ft_handle_redirections(tout, 1))
					return (ft_rewind_fds(tout), -1);
			tout->ret_built = ft_builtins(tout);
		}
		else
		{
			tout->list[tout->i] = fork();
			if (tout->list[tout->i] == 0)
				child_routine(tout);
			tout->b_or_w = 1;
			tout->i++;
		}
		tout->pipes_left--;
		tout->lst = ft_next_pipe(tout->lst);
	}
	ft_rewind_fds(tout);
	return (0);
}

int	ft_is_built(t_lst *lst)
{
	char	*str;

	if (!lst || !lst->str || !lst->str[0])
		return (0);
	str = lst->str;
	if (!nk_strcmp(str, "echo") || !nk_strcmp(str, "pwd") ||
		!nk_strcmp(str, "env") || !nk_strcmp(str, "cd") ||
		!nk_strcmp(str, "export") || !nk_strcmp(str, "unset") ||
		!nk_strcmp(str, "exit"))
		return (1);
	return (0);
}

int	ft_have_redirs(t_lst *lst)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3 || lst->token == 4)
			return (1);
		lst = lst->next;
	}
	return (0);
}
