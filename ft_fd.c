/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:58:20 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/26 23:58:21 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**create_pipe_arr(int nb_pipes)
{
	int	i;
	int	**pipefd;
	int	ret;

	pipefd = malloc(nb_pipes * sizeof(int *));
	if (pipefd == NULL)
		return (NULL);
	i = -1;
	while (++i < nb_pipes)
	{
		pipefd[i] = malloc(8);
		if (pipefd[i] == NULL)
			return (free_pipe_array(pipefd, i), NULL);
	}
	i = -1;
	while (++i < nb_pipes)
	{
		ret = pipe(pipefd[i]);
		if (ret == -1)
			return (ft_close_pipes(pipefd, i), NULL);
	}
	return (pipefd);
}

void	free_pipe_array(int **pipefd, int nb_pipes)
{
	int	i;

	if (!pipefd || !nb_pipes)
		return ;
	i = -1;
	while (++i < nb_pipes)
	{
		if (!pipefd[i])
			return ;
		free(pipefd[i]);
	}
	free(pipefd);
}

int	ft_close_pipes(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (close(pipefd[i][0]) || close(pipefd[i][1]))
			return (perror("close"), 1);
		i++;
	}
	return (0);
}
