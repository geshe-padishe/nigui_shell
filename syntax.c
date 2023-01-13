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

//synthax_error
//red_pipes_synthax
//synthax_checker

//free stuff to exit?	free(darr);    // or where else and exit
int	print_err(int err)
{
	if (err == -1)
		write(2, "Error malloc\n", 13);
	else if (err == -2)
		write(2, "Missing quote\n", 14);
	else if (err == -3)
		write(2, "Syntax error\n", 13);
	else if (err == -4)
		write(2, "Parse error\n", 12);
	return (0);
}

// Check if the recursivity covers all cases well 
static int	operator_check(char *line, char op)
{
	char	*tmp;

	if (!line)
		return (0);
	tmp = line;
	while (*tmp && *tmp == ' ')
		tmp++;
	if (!*tmp || (op == '|' && *tmp == op))
		return (print_err(-3));
	if (is_redir(op) && (is_operator(*tmp)) && tmp - line)
		return (print_err(-3));
	if (is_redir(op) && (is_operator(*tmp)) && op != *tmp)
		return (print_err(-3));
	if (is_redir(op) && (is_redir(*tmp)) && op == *tmp)
		if (is_operator(tmp[1]))
			return (print_err(-3));
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
			{
				print_err(-3);
				return (0);
			}
			if (!operator_check(line + 1, *line))
				return (0);
		}
		if (line && *line)
			line++;
	}
	return (1);
}
