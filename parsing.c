/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:33 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 20:02:07 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"
#include "minishell.h"

static void	interpret(char *str, int rev)
{
	if (!str)
		return ;
	while (*str)
	{
		if (is_quote(*str) && !rev)
			str = protect_content(str, rev);
		if (*str)
		{
			if (*str == '$' * -1 && rev)
				*str *= -1;
			str++;
		}
	}
}

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
		return (interpret(s, 0), 1);
	write(2, "Quote error\n", 12);
	return (0);
}

static void	rm_quote(t_lst *lst)
{
	char	*old;

	if (!lst)
		return ;
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

char	*x(char *line, char *hd, char *exp, int nb)
{
	if (nb == 1)
		return (line);
	if (nb == 2)
		return (hd);
	if (nb == 3)
		return (exp);
	return (line);
}

t_lst	*parse(char *line, int ext, t_dynarray *darr)
{
	char	*exp;
	char	*hd;
	t_lst	*lst;
	int		upd;

	upd = 1;
	hd = NULL;
	exp = NULL;
	if (!line || !quote_check(line))
		return (0);
	if (has_heredoc(line))
	{
		hd = mult_heredoc(line);
		upd = 2;
	}
	if (!syntax_check(x(line, hd, NULL, upd)))
		return (safe_free(line, hd), NULL);
	if (find_dollar(x(line, hd, NULL, upd)))
	{
		exp = my_expand(x(line, hd, NULL, upd), ext, darr);
		safe_free(line, hd);
		upd = 3;
	}
	interpret(x(line, hd, exp, upd), 1);
	lst = tokenize(x(line, hd, exp, upd));
	return (safe_free(line, x(line, hd, exp, upd)), rm_quote(lst), lst);
}
