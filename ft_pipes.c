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

int	ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
	int		pipes_left;
	int		fd_in;
	int		ret_built;
	int		ret_wait;
	int		b_or_w;
	t_lst	*start_lst;

	ft_print_list(lst);
	if (!lst)
		return (1);
	pipes_left = nb_pipes;
	pipefd = NULL;
	if (nb_pipes)
	{
		pipefd = create_pipe_arr(nb_pipes);
		if (!pipefd)
			return (perror("malloc"), 0);
	}
	i = 0;
	start_lst = lst;
	signal(SIGINT, SIG_IGN);
	while (lst && lst->str)
	{
		ret_built = -3;
		b_or_w = 0;
		if (!nb_pipes)
			ret_built = ft_builtins(find_bin_lst(lst), darr);
		if (ret_built == -3) //and if builtins return 0?
		{
			list[i] = fork();
			if (list[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in))
					return (ft_free_all(darr, start_lst, pipefd, nb_pipes), exit(1), 1);
				if 	(ft_handle_redirections(lst))
					return (ft_free_all(darr, start_lst, pipefd, nb_pipes), exit(1), 1);
				if (ft_handle_exec(find_bin_lst(lst), darr))
					return (ft_free_all(darr, start_lst, pipefd, nb_pipes), exit(127), 1);
				exit(1);
			}
			b_or_w = 1;
			i++; //PEUTETRE MONTER CA DANS LE if list[i] = 0
		}
		pipes_left--;
		lst = ft_next_pipe(lst);
	}
	ft_close_pipes(pipefd, nb_pipes);
	ret_wait = ft_wait_procs(i, list);
	if (b_or_w)
		g_vrac.status = ret_wait;
	else
		g_vrac.status = ret_built;
	signal(SIGINT, sigintHandler);
	return (free_pipe_array(pipefd, nb_pipes), free_lst(start_lst), 0);
}

int	ft_wait_procs(int ac, pid_t *list)
{
	int		i;
	int		status;
	pid_t	w;

	i = 0;
	while (i < ac)
	{
		w = waitpid(list[i], &status, 0);
		if (w == -1)
			perror("waitpid");
		i++;
	}
	return (WEXITSTATUS(status));
}

int	ft_builtins(t_lst *lst, t_dynarray *darr)
{
	char	**args;

	args = ft_splitargs(lst);
	if (!args)
		return (perror("malloc"), -2);
	if (!nk_strcmp(lst->str, "echo"))
		return (ft_echo(args + 1), 1);
	else if (!nk_strcmp(lst->str, "pwd"))
		return (ft_pwd(args + 1), 1);
	else if (!nk_strcmp(lst->str, "env"))
		return (ft_dyn_env(darr, args + 1), 1);
	else if (!nk_strcmp(lst->str, "cd"))
		return (ft_cd(args + 1), 1);
	else if (!nk_strcmp(lst->str, "export"))
		return (ft_export(darr, args + 1), 1);
	else if (!nk_strcmp(lst->str, "unset"))
		return (ft_unset(darr, args + 1), 1);
	else if (!nk_strcmp(lst->str, "exit"))
		return (ft_exit(args + 1, darr), 1); //ajouter lst pour free avant exit
	return (printf("I FREE ARGS?\n"), free(args), -3);
}
