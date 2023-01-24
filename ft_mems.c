#include "minishell.h"

void	ft_free_env(t_dynarray *darr)
{
	char		**env;
	uint64_t	i;

	i = 0;
	env = darr->list;
	while (i < darr->nb_cells)
	{
		free(env[i]);
		i++;
	}
	free_dynarray(darr);
	rl_clear_history();
}

void	ft_free_all(t_dynarray *darr, t_lst *lst, int **pipefd, int nb_pipes)
{
	ft_free_env(darr);
	free_lst(lst);
	free_pipe_array(pipefd, nb_pipes);
}
