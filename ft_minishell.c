#include "minishell.h"

int	ft_handle_pipe(int **pipefd, int pipes_left, int nb_pipes, int *fd_in)
{
	int	fd_out;

	if (pipes_left != nb_pipes)
	{
		*fd_in = dup2(pipefd[nb_pipes - pipes_left - 1][0], STDIN_FILENO);
		if (*fd_in == -1)
			return (perror("dup2"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
	}
/*separation*/
	if (pipes_left != 0)
	{
		fd_out = dup2(pipefd[nb_pipes - pipes_left][1], STDOUT_FILENO);
		if (fd_out == -1)
			return (perror("dup2"), ft_close_pipes(pipefd, nb_pipes),
				free_pipe_array(pipefd, nb_pipes), -1);
	}
	return (ft_close_pipes(pipefd, nb_pipes), 0);
}

t_lst *find_bin_lst(t_lst *lst)
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

//	lst->str = "ls -la fsdljgod"
//	lst->token = 0 string
//				= 1 pipe
//				= 2 >
//				= 3 <
//				= 4 >>
//				= 5 <<
//
