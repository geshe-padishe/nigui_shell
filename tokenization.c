/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 02:32:08 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/29 02:33:02 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

static void	push_token(char *str, t_lst *lst, int op)
{
	t_lst	*new;

	printf("push token\n");
	new = new_lst();
	if (!new)
		return ;
	new->str = str;
	if (op == 1)
		new->token = recognize_op(new->str);
	else
		new->token = 0;
	new->prev = NULL;
	new->next = NULL;
	push_lst(new, lst);
}

static char	*find_str(char *line, t_lst *lst)
{
	char	*str;
	int		i;
	char	c;

	i = 0;
	printf("find_str\n");
	while (line[i] && !is_space(line[i]) && !is_operator(line[i]))
	{
		printf("char is: %c\n", line[i]);
		if (is_quote(line[i]))
		{
			c = line[i++];
			line[i - 1] *= -1;
			while (line[i] && line[i] != c)
				i++;
			line[i] *= -1;
			if (line[i + 1])
				i++;
		}
		if (line[i] && !is_space(line[i]) && !is_operator(line[i]))
			i++;
	}
	str = ft_substr(line, 0, i);
	push_token(str, lst, 0);
	return (line + i - 1);
}

static char	*find_operator(char *line, t_lst *lst)
{
	char	*op;
	int		i;
	char	c;

	i = 0;
	c = *line;
	while (line[i] && line[i]==c)
		i++;
	op = ft_substr(line, 0, i);
	push_token(op, lst, 1);
	return (line + i - 1);
}

t_lst	*tokenize(char *line)
{
	t_lst	*lst;

	printf("tokenize\n");
	lst = new_lst();
	while (line && *line)
	{
		if (is_operator(*line))
			line = find_operator(line, lst);
		else if (!is_space(*line))
			line = find_str(line, lst);
		line++;
	}
	return (lst);
}
