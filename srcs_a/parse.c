/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admaupie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:54:56 by admaupie          #+#    #+#             */
/*   Updated: 2022/07/27 19:09:44 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

int	get_word(char *buffer, t_lst *new)
{
	int	i;
	int	c;

	i = 0;
	c = ' ';
	while (buffer[i] && (c != ' ' || !is_sep(buffer[i])))
	{
		if (c == ' ' && (buffer[i] == SIMPLE_QUOTE || buffer[i] == 34))
			c = buffer[i];
		else if (c != ' ' && buffer[i] == c)
			c = ' ';
		i++;
	}
	if (c != ' ')
		return (-2);
	new->str = ft_strndup(buffer, i);
	if (!new->str)
		return (-1);
	return (1);
}

void	expand(t_lst *lst, t_dynarray *darr)
{
	t_lst	*ptr;
	int		i;
	int		c;

	ptr = lst->next;
	while (ptr)
	{
		if (ptr->token == 0)
		{
			i = 0;
			c = 0;
			while (ptr->str && ptr->str[i])
			{
				if (c == 0 && (ptr->str[i] == 39 || ptr->str[i] == 34))
					c = ptr->str[i];
				else if (c != 0 && ptr->str[i] == c)
					c = 0;
				else if (ptr->str[i] == '$' && c != SIMPLE_QUOTE
						&& ptr->str[i + 1] && ptr->str[i + 1] != ' ')
					i = i + ft_replacedollar(ptr, i, c, darr);
				i++;
			}
		}
		ptr = ptr->next;
	}
}

int	parse(char *line_buffer, t_dynarray *darr)
{
	int		i;
	int		len;
	t_lst	*lst;

	lst = ft_lstnew();
	if (!lst)
		return (print_err(-1));
	i = 0;
	while (line_buffer && line_buffer[i])
	{
		len = 1;
		if (!is_sep(line_buffer[i]) && line_buffer[i] != ' ')
			len = push_word(lst, line_buffer + i);
		else if (line_buffer[i] != ' ')
			len = push_sep(lst, line_buffer + i);
		if (len < 0)
			return (print_err(len) + free_lst(lst));
		i = i + len;
	}
//	if (!ft_verif(lst))
//		return (print_err(-4));
	ft_printlst(lst);
	expand(lst, darr);
	ft_printlst(lst);
	ft_pipes(lst, ft_pipes_left(lst), darr);
	free_lst(lst);
	return (1);
}
