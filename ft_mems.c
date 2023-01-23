#include "dynarray.h"

void	ft_free_all(t_dynarray *darr)
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
