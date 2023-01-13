/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_dquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 06:52:08 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/14 06:53:20 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
char	quote_find(int quote)
{
	if (quote == 1)
		return ('\0');
	else if (quote == -1)
		return ('\'');
	else if (quote == -2)
		return ('"');
	else
		return ('\0');
}

void	close_quote(int quote)
{
	char	*line;
	char	opened;
	int		closed;

	opened = quote_find(quote);
	line = readline("dquote>");
	closed = quote_check(line, opened);
	printf("closed = %d\n", closed);  
	if (closed < 0)
		close_quote(closed);
}    

int	quote_check(char *s)
{
	char	curr_quote;

	curr_quote = '\0';
	while (*s)
	{
		if(*s == curr_quote)
			curr_quote = '\0';
		else if ((*s == '"' || *s == '\'') && curr_quote == '\0')
			curr_quote = *s;
		s++;
	}
	if (curr_quote == '\0')
		return (1);
	{
		if (curr_quote == '\'')
			return (-1);
		else if (curr_quote == '"')
			return (-2);
		return (quote);
	}
}
*/
