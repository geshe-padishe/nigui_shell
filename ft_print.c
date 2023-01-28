/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:01 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/28 01:25:33 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_env(t_dynarray *darr)
{
	uint64_t	i;

	i = 0;
	while (i < darr->nb_cells && ((char **)darr->list)[i])
	{
		printf("%s\n", ((char **)darr->list)[i]);
		i++;
	}
	return (0);
}

int	ft_dyn_env(t_dynarray *darr, char **str)
{
	uint64_t	i;

	if (*str)
		return (write(2, "env: Too many arguments\n", 24), 1);
	i = 0;
	while (i < darr->nb_cells && ((char **)darr->list)[i])
	{
		printf("%s\n", ((char **)darr->list)[i]);
		i++;
	}
	return (free(str - 1), 0);
}

void	ft_print_pipes(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		printf("-----------------------------\n");
		printf("pipefd[%d][0] = %d\n", i, pipefd[i][0]);
		printf("pipefd[%d][1] = %d\n", i, pipefd[i][1]);
		printf("-----------------------------\n");
		i++;
	}
}

void	ft_print_list(t_lst *token)
{
	while (token != NULL)
	{
		printf("token->str = %s\n", token->str);
		token = token->next;
	}
}
