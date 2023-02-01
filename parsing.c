/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:33 by hkhater           #+#    #+#             */
/*   Updated: 2023/02/01 01:46:05 by ngenadie         ###   ########.fr       */
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
	char	*exp_hd[2];
	t_lst	*lst;
	int		upd;

	upd = 1;
	ft_memset(&exp_hd, 0, sizeof(char **));
	if (!line || !quote_check(line))
		return (0);
	if (has_heredoc(line))
	{
		exp_hd[1] = mult_heredoc(line);
		upd = 2;
	}
	if (!syntax_check(x(line, exp_hd[1], NULL, upd)))
		return (safe_free(line, exp_hd[1]), NULL);
	if (find_dollar(x(line, exp_hd[1], NULL, upd)))
	{
		exp_hd[0] = my_expand(x(line, exp_hd[1], NULL, upd), ext, darr);
		safe_free(line, exp_hd[1]);
		upd = 3;
	}
	interpret(x(line, exp_hd[1], exp_hd[0], upd), 1);
	lst = tokenize(x(line, exp_hd[1], exp_hd[0], upd));
	return (safe_free(line, x(line, exp_hd[1], exp_hd[0], upd)),
		rm_quote(lst), lst);
}
