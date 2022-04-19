/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 18:00:34 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/19 17:03:16 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_is_null(t_split *split)
{
	perror("parse(): Error during split");
	free(split->split);
	free(split);
	return (-1);
}

int	parse_split_ret_error(t_split *split, int i)
{
	perror("parse(): Error encountered while splitting");
	while (split->split[i] != NULL)
		free(split->split[i++]);
	free(split->split);
	free(split);
	return (-1);
}

void	display_token_propertie(t_token *token, int i)
{
	if (token[i].is_redirection_input == 1)
		printf("\ttoken[%d]->is a redirection input\n", i);
	else if (token[i].is_redirection_output == 1)
		printf("\ttoken[%d]->is a redirection output\n", i);
	else if (token[i].is_here_doc == 1)
		printf("\ttoken[%d]->is a here document\n", i);
	else if (token[i].is_append_output == 1)
		printf("\ttoken[%d]->is a append output\n", i);
	else if (token[i].is_word == 1)
		printf("\ttoken[%d]->is a word\n", i);
	else if (token[i].is_wrong == 1)
		printf("\ttoken[%d]->is wrong\n", i);
}

int	process_split(t_split *split, int i)
{
	t_token	*token;

	token = ft_token(split);
	i = 0;
	if (token == NULL)
	{
		perror("process_split(): Error encountered while tokenizing split");
		return (-1);
	}
	while (token[i].elem != NULL)
	{
		which_is(token, i);
		printf("token[%d] = %s\n", i, token[i].elem);
		display_token_propertie(token, i);
		i++;
	}
	unload(split, token);
	return (0);
}

int	check_line(char *str)
{
	int	i;
	int	in_singlequote;
	int	in_doublequote;

	i = 0;
	in_singlequote = 0;
	in_doublequote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && in_doublequote == 0 && in_singlequote == 1)
				in_singlequote = 0;
		else if (str[i] == '\'' && in_doublequote == 0 && in_singlequote == 0)
				in_singlequote = 1;
		else if (str[i] == '\"' && in_singlequote == 0 && in_doublequote == 1)
				in_doublequote = 0;
		else if (str[i] == '\"' && in_singlequote == 0 && in_doublequote == 0)
				in_doublequote = 1;
		i++;
	}
	if (in_singlequote == 1 || in_doublequote == 1)
		return (-1);
	else
		return (0);
}

int	parse(char *line_buffer)
{
	t_split	*split;
	int		i;

	if (check_line(line_buffer) == -1)
	{
		perror("parse(): Syntax error, no closing quote");
		return (-1);
	}
	i = 0;
	split = (t_split *)malloc(sizeof(t_split));
	if (split == NULL)
	{
		perror("parse(): Error allocating split structure");
		return (-1);
	}
	ft_memset((void *)split, 0, sizeof(t_split));
	if (redo_split(line_buffer, split) == -1)
		return (parse_split_ret_error(split, i));
	else
	{
		if (split->split[i] == NULL && line_buffer == NULL)
			return (split_is_null(split));
		else
			return (process_split(split, i));
	}
	return (0);
}