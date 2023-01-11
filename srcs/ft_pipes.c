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

int	ft_pipes(t_lst *lst, int nb_pipes, t_dynarray *darr)
{
	int		**pipefd;
	int		i;
	pid_t	list[nb_pipes + 1];
	int		pipes_left;
	int		fd_in;
	int		ret;
	t_lst	*start_lst;

	ft_print_list(lst);
	pipes_left = nb_pipes;
	pipefd = create_pipe_arr(nb_pipes);
	if (!pipefd)
		return (perror("malloc"), 0);
	i = 0;
	start_lst = lst;
	while (lst && lst->str)
	{
		lst = start_lst;
		ret = ft_builtins(lst, darr, nb_pipes);
		dprintf(2, "RET = %d\n", ret);
		if (ret == -1)
		{
			list[i] = fork();
			dprintf(2, "FORKING pid = %d\n", list[i]);
			if (list[i] == 0)
			{
				if (ft_handle_pipe(pipefd, pipes_left, nb_pipes, &fd_in) ||
					ft_handle_redirections(start_lst) ||
					ft_handle_exec(start_lst, darr) || true)
					return (ft_close_pipes(pipefd, nb_pipes),
							free_pipe_array(pipefd, nb_pipes), 1);
			}
			i++;
		}
		pipes_left--;
		lst = ft_next_pipe(start_lst);
		if (lst)
			start_lst = lst->next;
	}
	ft_close_pipes(pipefd, nb_pipes);
	ft_wait_procs(i, list);
	return (free_pipe_array(pipefd, nb_pipes), ret);
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
		printf("status = %d\n", status);
		if (w == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			printf("terminé, code=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("tué par le signal %d\n", WTERMSIG(status));
		else if (WIFSTOPPED(status))
			printf("arrêté par le signal %d\n", WSTOPSIG(status));
		else if (WIFCONTINUED(status))
			printf("relancé\n");
		i++;
	}
	return (0);
}

int	ft_builtins(t_lst *lst, t_dynarray *darr, int nb_pipes)
{
	char **args;

	args = ft_splitargs(lst);
	ft_print_args(args);
	if (!lst)
		return (0);
	while (lst && lst->token != 0)
		lst = lst->next;
	if (!nk_strcmp(lst->str, "cd"))
		return (ft_cd(args + 1, ft_getenvval("HOME", darr, 1, 0), nb_pipes), 0);
	else if (!nk_strcmp(lst->str, "export"))
		return (ft_export(darr, args + 1, nb_pipes), 0);
	else if (!nk_strcmp(lst->str, "unset"))
		return (ft_unset(darr, args + 1, nb_pipes), 0);
	else if (!nk_strcmp(lst->str, "exit"))
		return (dprintf(2, "builtins return exit\n"), ft_exit(args, nb_pipes));
	return (-1);
}
