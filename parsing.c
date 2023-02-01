/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <ngenadie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:33 by hkhater           #+#    #+#             */
/*   Updated: 2023/02/01 03:24:41 by ngenadie         ###   ########.fr       */
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

int	init_parse(int *upd, char **exp_hd)
{
	*upd = 1;
	exp_hd[0] = NULL;
	exp_hd[1] = NULL;
	ft_memset(&exp_hd, 0, sizeof(char **));
	return (1);
}

t_lst	*parse(char *line, int ext, t_dynarray *darr)
{
	char	*exp_hd[2];
	t_lst	*lst;
	int		upd;

	init_parse(&upd, exp_hd);
	if (!line || !quote_check(line))
		return (0);
	if (has_heredoc(line))
	{
		exp_hd[1] = mult_heredoc(line, ext, darr);
		upd = 2;
	}
	if (!syntax_check(x(line, exp_hd[1], NULL, upd)))
		return (safe_free(line, exp_hd[1]), NULL);
	if (find_dollar(x(line, exp_hd[1], NULL, upd)))
	{
		dprintf(2, "line = %s\n", line);
		dprintf(2, "exp_hd = %s\n", exp_hd[1]);
		exp_hd[0] = my_expand(x(line, exp_hd[1], NULL, upd), ext, darr);
			safe_free(line, exp_hd[1]);
		upd = 3;
	}
	interpret(x(line, exp_hd[1], exp_hd[0], upd), 1);
	lst = tokenize(x(line, exp_hd[1], exp_hd[0], upd));
	return (safe_free(line, x(line, exp_hd[1], exp_hd[0], upd)),
		rm_quote(lst), lst);
}
