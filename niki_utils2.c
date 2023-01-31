/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niki_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 21:10:03 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 21:10:18 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*find_bin_lst(t_lst *lst)
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
