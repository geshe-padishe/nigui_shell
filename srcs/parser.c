/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:00:34 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/17 23:49:05 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_is_null(t_split *split)
{
	perror("parse(): Error during split");
	free(split->split);
	free(split);
}

void	parse_split_ret_error(t_split *split, int i)
{
	perror("parse(): Error encountered, freeing and exiting");
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
}

void	process_split(t_split *split, int i)
{
	t_token	*token;

	token = ft_token(split);
	if (token == NULL)
	{
		perror("process_split(): token scuffed");
		return ;
	}
	while (token[i].elem != NULL)
	{
		which_is(token, i);
		printf("token[%d] = %s\n", i, token[i].elem);
		i++;
	}
	unload(split, token);
}

void	parse(char *line_buffer)
{
	t_split	*split;
	int		i;

	i = 0;
	split = (t_split *)malloc(sizeof(t_split));
	if (split == NULL)
	{
		perror("parse(): Error allocating split structure");
		return ;
	}
	ft_memset((void *)split, 0, sizeof(t_split));
	count_quotes(line_buffer, split);
	if (redo_split(line_buffer, split) == -1)
		parse_split_ret_error(split, i);
	else
	{
		if (split->split[i] == NULL && line_buffer == NULL)
			split_is_null(split);
		else
			process_split(split, i);
	}
}
