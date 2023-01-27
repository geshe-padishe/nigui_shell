/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niki_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:01:52 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/27 00:01:53 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_free(int **pipefd, int nb_pipes, t_lst *lst, t_dynarray *darr)
{
	if (lst)
		free_lst(lst);
	if (ft_close_pipes(pipefd, nb_pipes))
		return (free_pipe_array(pipefd, nb_pipes),
			ft_free_all(darr, lst, pipefd, nb_pipes), 1);
	free_pipe_array(pipefd, nb_pipes);
	ft_free_all(darr, lst, pipefd, nb_pipes);
	return (0);
}
