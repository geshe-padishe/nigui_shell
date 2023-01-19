#include "minishell.h"

t_lst	*ft_next_pipe(t_lst *lst)
{
	while (lst && lst->token != 1)
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
	t_lst	*start_lst;

	ft_print_list(lst);
	if (!lst)
		return (0);
	pipes_left = nb_pipes;
	pipefd = create_pipe_arr(nb_pipes);
	if (!pipefd)
		return (perror("malloc"), 0);
	i = 0;
	start_lst = lst;
	while (lst && lst->str)
	{
		ret = 0;
		lst = start_lst;
		b_or_w = 0;
		if (!nb_pipes)
			ret = ft_builtins(lst, darr, status);
		if (!ret)
		{
			list[i] = fork();
			if (list[i] == 0)
			{
				if (ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in) ||
					ft_handle_redirections(start_lst))
					return (ft_close_free(pipefd, nb_pipes,
							lst, darr), exit(1), 1);
				if (ft_handle_exec(start_lst, darr, status))
					return (ft_close_free(pipefd, nb_pipes,
							lst, darr), exit(127), 1);
				exit(1);
			}
			b_or_w = 1;
			i++; //PEUTETRE MONTER CA DANS LE if list[i] = 0
		}
		pipes_left--;
		lst = ft_next_pipe(start_lst);
		if (lst)
			start_lst = lst->next;
	}
	ft_close_pipes(pipefd, nb_pipes);
	if (b_or_w)
		*status = ft_wait_procs(i, list);
	else
		*status = ret;
	return (free_pipe_array(pipefd, nb_pipes), 1);
}

int	ft_wait_procs(int ac, pid_t *list)
{
	int i;
	int status;
	pid_t w;

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
	char **args;

	args = ft_splitargs(lst);
	if (!args)
		return (0);
	while (lst && lst->token != 0)
		lst = lst->next;
	if (!nk_strcmp(lst->str, "cd"))
		return (ft_cd(args + 1));
	else if (!nk_strcmp(lst->str, "export"))
		return (ft_export(darr, args + 1));
	else if (!nk_strcmp(lst->str, "unset"))
		return (ft_unset(darr, args + 1));
	else if (!nk_strcmp(lst->str, "exit"))
		return ((unsigned char)ft_exit(args + 1, darr, *status));
	return (free(args), -1);
}
