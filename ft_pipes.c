/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:00:38 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 21:05:30 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_next_pipe(t_lst *lst)
{
	while (lst && lst->token != 1)
		lst = lst->next;
	if (lst)
		lst = lst->next;
	return (lst);
}

int	ft_pipes_left(t_lst *lst)
{
	int	pipes;

	pipes = 0;
	if (!lst)
		return (-1);
	while (lst->next)
	{
		if (lst->next->token == 1)
			pipes++;
		lst = lst->next;
	}
	return (pipes);
}

int	ft_pipes(t_lst *lst, t_tout *tout)
{
	tout->lst = lst;
	tout->pipes_left = ft_pipes_left(lst);
	tout->nb_pipes = tout->pipes_left;
	tout->b_or_w = 0;
	if (tout->nb_pipes)
	{
		tout->pipefd = create_pipe_arr(tout->nb_pipes);
		if (!tout->pipefd)
			return (perror("malloc"), 0);
	}
	signal(SIGINT, SIG_IGN);
	launch_child(tout);
	ft_close_pipes(tout->pipefd, tout->nb_pipes);
	tout->ret_wait = ft_wait_procs(tout->i, tout->list);
	if (tout->b_or_w)
		g_vrac.status = tout->ret_wait;
	else
		g_vrac.status = tout->ret_built;
	signal(SIGINT, siginthandler);
	return (free_pipe_array(tout->pipefd, tout->nb_pipes),
		free_lst(first_lst(lst)), 0);
}

int	ft_wait_procs(int ac, pid_t *list)
{
	int		i;
	int		status;
	int		status2;
	pid_t	w;

	i = 0;
	status = 0;
	while (i < ac)
	{
		w = waitpid(list[i], &status, 0);
		if (w == -1)
			perror("waitpid");
		i++;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			put_err("Quit (core dumped)\n");
		if (WTERMSIG(status) == 2)
			put_err("\n");
		status2 = WTERMSIG(status) + 128;
	}
	if (WIFEXITED(status))
		status2 = WEXITSTATUS(status);
	return (status2);
}

int	ft_builtins(t_tout *tout)
{
	char	**args;
	t_lst	*lst;

	lst = find_bin_lst(tout->lst);
	if (!lst)
		return (0);
	args = ft_splitargs(lst);
	if (!args)
		return (perror("malloc"), 1);
	if (!nk_strcmp(lst->str, "echo"))
		return (ft_echo(args + 1));
	else if (!nk_strcmp(lst->str, "pwd"))
		return (ft_pwd(args + 1));
	else if (!nk_strcmp(lst->str, "env"))
		return (ft_dyn_env(tout->darr, args + 1));
	else if (!nk_strcmp(lst->str, "cd"))
		return (ft_cd(args + 1));
	else if (!nk_strcmp(lst->str, "export"))
		return (ft_export(tout->darr, args + 1, (char **)tout->darr->list));
	else if (!nk_strcmp(lst->str, "unset"))
		return (ft_unset(tout->darr, args + 1));
	else if (!nk_strcmp(lst->str, "exit"))
		return (ft_exit(tout, args + 1));
	return (free(args), -3);
}
