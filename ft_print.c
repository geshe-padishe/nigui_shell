/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:47:01 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/29 04:37:25 by ngenadie         ###   ########.fr       */
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

void	print_quoted(char *str)
{
	int	i;

	i = 0;
	put_err("'");
	put_err(str);
	put_err("'");
}

void	print_lst(t_lst *lst)
{
	while (lst && lst->str)
	{
		printf("%s\n", lst->str);
		lst = lst->next;
	}
	if (lst == NULL)
		printf("lst(nil)\n");
}
