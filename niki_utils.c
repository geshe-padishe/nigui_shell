#include "minishell.h"

int	ft_close_free(int **pipefd, int nb_pipes, t_lst *lst, t_dynarray *darr)
{
	if (lst)
		free_lst(lst);
	if (ft_close_pipes(pipefd, nb_pipes))
		return (free_pipe_array(pipefd, nb_pipes),
			ft_free_all(darr), 1);
	free_pipe_array(pipefd, nb_pipes);
	ft_free_all(darr);
	return (0);
}
