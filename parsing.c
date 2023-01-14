/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:33 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/14 04:10:24 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

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
			if (*str == '$' * -1)
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

t_lst	*parse(char *line, int ext, t_dynarray *darr)
{
	char	*expanded;
	t_lst	*lst;

	if (!line)
		return (0);
	if (!quote_check(line))
		return (0);
	interpret(line, 0);
	if (!syntax_check(line))
		return (0);
	expanded = my_expand(line, ext, darr);
	if (!expanded)
		return (0);
	interpret(expanded, 1);
	printf("expanded and interpreted\n");
	lst = tokenize(expanded);
	printf("tokenized\n");
	rm_quote(lst);
	printf("removed quotes\n");
	ft_printlst(lst);
	return (lst);
}
