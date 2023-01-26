/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitargs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 03:48:03 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/26 03:52:12 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_count_args(t_lst *lst)
{
	int	args;

	args = 0;
	while (lst && lst->token != 1)
	{
		if (lst->token == 0)
			args++;
		if (lst->token >= 2 && lst->token <= 5)
			lst = lst->next;
		lst = lst->next;
	}
	return (args);
}

char	**ft_splitargs(t_lst *lst)
{
	t_lst	*start_lst;
	char	**argv;
	size_t	args;
	size_t	i;

	start_lst = lst;
	args = ft_count_args(lst);
	i = 0;
	argv = malloc(sizeof(char **) * (args + 1));
	if (!argv)
		return (NULL);
	while (start_lst && start_lst->token != 1)
	{
		if (start_lst->token == 0)
			argv[i++] = start_lst->str;
		if (start_lst->token >= 2 && start_lst->token <= 5)
			start_lst = start_lst->next;
		start_lst = start_lst->next;
	}
	argv[i] = NULL;
	return (argv);
}
