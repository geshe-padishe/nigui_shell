/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 09:00:57 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/22 07:33:52 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

char	*put_err(char *str)
{
	if (str)
		while (*str)
			write(2, str++, 1);
	return (NULL);
}

static char	*syntax_error(char c)
{
	char	token[4];

	token[0] = c;
	token[1] = '\'';
	token[2] = '\n';
	token[3] = '\0';
	if (is_operator(c))
	{
		put_err(SYNTAX_ERR);
		put_err(token);
	}
	else
	{
		put_err(SYNTAX_ERR);
		put_err("newline'\n");
	}
	return (NULL);
}

static int	operator_check(char *line, char op)
{
	char	*tmp;

	if (!line)
		return (0);
	tmp = line;
	while (*tmp && *tmp == ' ')
		tmp++;
	if (!*tmp)
		return (put_err(SYNTAX_ERR), put_err("newline'\n"), 0);
	if (op == '|' && *tmp == op)
		return (syntax_error(op), 0);
	if (is_redir(op) && (is_operator(*tmp)) && tmp - line)
		return (syntax_error(op), 0);
	if (is_redir(op) && (is_operator(*tmp)) && op != *tmp)
		return (syntax_error(op), 0);
	if (is_redir(op) && (is_redir(*tmp)) && op == *tmp)
		if (is_operator(tmp[1]))
			return (syntax_error(op), 0);
	if (is_redir(*tmp))
		return (operator_check(tmp + 1, *tmp));
	return (1);
}

int	syntax_check(char *line)
{
	int	empty;

	if (!line)
		return (0);
	empty = 1;
	while (*line)
	{
		if (!is_operator(*line) && *line != ' ' && empty)
			empty = 0;
		if (is_operator(*line))
		{
			if (empty && *line == '|')
				return (syntax_error('|'), 0);
			if (!operator_check(line + 1, *line))
				return (0);
		}
		if (line && *line)
			line++;
	}
	return (1);
}
