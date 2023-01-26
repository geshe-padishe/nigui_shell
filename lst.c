/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:16:13 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/26 07:25:52 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

t_lst	*new_lst(void)
{
	t_lst	*new;

	new = malloc(sizeof(t_lst));
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->token = -1;
	return (new);
}

void	push_first_lst(t_lst *new, t_lst *lst)
{
	lst->str = new->str;
	lst->token = new->token;
	lst->next = NULL;
	lst->prev = NULL;
	free (new);
}

void	push_lst(t_lst *new, t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	if (lst->str == NULL)
	{
		push_first_lst(new, lst);
		return ;
	}
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	else
		lst = new;
	return ;
}

void	free_lst(t_lst *src)
{
	t_lst	*next;

	while (src->prev)
		src = src->prev;
	while (src)
	{
		next = src->next;
		if (src->str)
			free(src->str);
		src->str = NULL;
		free(src);
		src = next;
	}
	src = 0;
	next = 0;
}

void	ft_printlst(t_lst *a)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = a;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	printf("TOKENS:\n");
	while (tmp)
	{
		if (tmp->str == NULL)
			printf("maillon nul\n");
		if (tmp->str)
			printf("%d -> %s\n", i + 1, tmp->str);
		tmp = tmp->next;
		i++;
	}
}

t_lst	*first_lst(t_lst *lst)
{
	while (lst && lst->prev)
		lst = lst->prev;
	return (lst);
}
