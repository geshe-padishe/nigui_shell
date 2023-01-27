/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mems.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:03:53 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 04:23:11 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_free_bcwrd(t_dynarray *darr, int i)
{
	char	**envp;

	envp = darr->list;
	while (i >= 0)
	{
		printf("i = %d\n", i);
		free(envp[i]);
		i--;
	}
	free_dynarray(darr);
}
