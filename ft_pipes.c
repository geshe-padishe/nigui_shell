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

int	ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr, int *status)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
	int		pipes_left;
	int		fd_in;
	int		ret;
	int		b_or_w;
	//t_lst	*start_lst;

	ft_print_list(lst);
	if (!lst)
		return (0);
	pipes_left = nb_pipes;
	pipefd = create_pipe_arr(nb_pipes);
	if (!pipefd)
		return (perror("malloc"), 0);
	i = 0;
	//start_lst = lst;
	while (lst && lst->str)
	{
		ret = -3;
		b_or_w = 0;
		if (!nb_pipes)
			ret = ft_builtins(find_bin_lst(lst), darr, status);
		if (ret == -3) //and if builtins return 0?
		{
			list[i] = fork();
			if (list[i] == 0)
			{
				if (nb_pipes)
					if (ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in))
						return (ft_free_all(darr), free_lst(lst), exit(1), 1);
				if 	(ft_handle_redirections(lst))
					return (ft_free_all(darr), free_lst(lst), exit(1), 1);
				if (ft_handle_exec(find_bin_lst(lst), darr, status))
					return (ft_free_all(darr), free_lst(lst), exit(127), 1);
				exit(1);
			}
			b_or_w = 1;
			i++; //PEUTETRE MONTER CA DANS LE if list[i] = 0
		}
		pipes_left--;
		lst = ft_next_pipe(lst);
	}
	ft_close_pipes(pipefd, nb_pipes); //check if nb_pipes == 0
	if (b_or_w)
		*status = ft_wait_procs(i, list);
	else
		*status = ret;
	return (free_pipe_array(pipefd, nb_pipes), 1);
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

int	ft_builtins(t_lst *lst, t_dynarray *darr, int *status)
{
	char	**args;

	args = ft_splitargs(lst);
	if (!args)
		return (printf("unable to make args\n"), -2);
	if (!nk_strcmp(lst->str, "cd"))
		return (ft_cd(args + 1));
	else if (!nk_strcmp(lst->str, "export"))
		return (ft_export(darr, args + 1));
	else if (!nk_strcmp(lst->str, "unset"))
		return (ft_unset(darr, args + 1));
	else if (!nk_strcmp(lst->str, "exit"))
		return ((unsigned char)ft_exit(args + 1, darr, *status));
	return (free(args), -3);
}
