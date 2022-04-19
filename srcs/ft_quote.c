/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 03:33:01 by gfritsch          #+#    #+#             */
/*   Updated: 2022/04/19 17:23:55 by gfritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted_good(char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (ft_strlen(str) == 1)
		return (-1);
	while (str[i] && (str[i] != '\'' || str[i] != '\"'))
		i++;
	if (str[i] == '\'' || str[i] == '\"') 
		quote = str[i];
	while (str[i])
	{
		if (i > 0 && str[i] == quote)
			return (0);
		i++;
	}
	return (-1);
}

void	to_quote_or_not_to_quote(char *str, int i, t_split *split)
{
	if (((str[i] == '\'') || (str[i] == '\"')) && split->quote == 0)
		split->quote = str[i];
	else if ((str[i] == '\'' && split->quote == '\'')
		|| (str[i] == '\"' && split->quote == '\"'))
		split->quote = 0;
}

void	index_to_quote_or_not_to_quote(char *str, int i, t_index *index)
{
	if (str[i])
	{
		if (((str[i] == '\'') || (str[i] == '\"')) && index->quote == 0)
			index->quote = str[i];
		else if ((str[i] == '\'' && index->quote == '\'')
		|| (str[i] == '\"' && index->quote == '\"'))
			index->quote = 0;
	}
}
