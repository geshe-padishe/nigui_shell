/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:33 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/29 15:45:57 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"
#include "minishell.h"

static int	quote_check(char *s)
{
	char	curr_quote;

	curr_quote = '\0';
	while (*s)
	{
		if (*s == curr_quote)
			curr_quote = '\0';
		else if (is_quote(*s) && curr_quote == '\0')
			curr_quote = *s;
		s++;
	}
	if (curr_quote == '\0')
		return (1);
	write(2, "Quote error\n", 12);
	return (0);
}

static void	interpret(char *str, int rev)
{
	if (!str)
		return ;
	while (*str)
	{
		if (is_quote(*str))
			str = protect_content(str, rev);
		if (*str)
		{
			if (*str == '$' * -1 && rev)
				*str *= -1;
			str++;
		}
	}
}

static void	rm_quote(t_lst *lst)
{
	char	*old;

	while (lst && lst->str)
	{
		if (lst->token == 0)
		{
			old = lst->str;
			if (has_quote(old))
				lst->str = dup_quote(old);
		}
		lst = lst->next;
	}
}

char	*mult_heredoc(char *line, int ext, t_dynarray *darr)
{
	char	*last;
	char	*tmp;
	int		nb;

	tmp = has_heredoc(line);
	last = line;
	nb = 0;
	if (!tmp)
		return (line);
	while (tmp)
	{
		tmp = has_heredoc(tmp);
		nb++;
	}
	while (nb--)
	{
		last = heredoc(last, ext, darr);
		printf("last is %s\n", last);
	}
	return (last);
}

t_lst	*parse(char *line, int ext, t_dynarray *darr)
{
	char	*expanded;
	char	*hd;
	t_lst	*lst;

	if (!line)
		return (0);
	if (!quote_check(line))
		return (0);
	hd = mult_heredoc(line, ext, darr);
	interpret(line, 0);
	if (!syntax_check(hd))
		return (0);
	expanded = my_expand(hd, ext, darr);
	if (!expanded)
		return (0);
	interpret(expanded, 1);
	lst = tokenize(expanded);
	interpret(line, 0);
	if (!strcmp(line, expanded))
		free(expanded);
	if (lst)
		return (rm_quote(lst), lst);
	return (NULL);
}
