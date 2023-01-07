#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	spe_count_words(char *str)
{
	int	w;
	int	i;
	int	c;

	c = ' ';
	w = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && c == ' ')
			i++;
		if (str[i])
			w++;
		while (str[i] && (c != ' ' || str[i] != c))
		{
			if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
				c = str[i];
			else if (c != ' ' && str[i] == c)
				c = ' ';
			i++;
		}
	}
	return (w);
}

int	spe_lenword(char *str)
{
	char	c;
	int		i;

	c = ' ';
	i = 0;
	while (str[i] && (c != ' ' || str[i] != c))
	{
		if (c == ' ' && (str[i] == SIMPLE_QUOTE || str[i] == 34))
			c = str[i];
		else if (c != ' ' && str[i] == c)
			c = ' ';
		i++;
	}
	return (i);
}

char	*spe_get_word(char *str, int n)
{
	int		w;
	int		i;
	int		j;
	char	*new;

	j = 0;
	w = 0;
	i = 0;
	while (w != n)
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			w++;
		i = i + spe_lenword(str + i);
	}
	while (str[i] && str[i] == ' ')
			i++;
	j = spe_lenword(str + i);
	new = ft_strndup(str + i, j);
	if (!new)
		return (NULL);
	return (new);
}

//char	**ft_splitargs(t_lst *lst)
//{
//	char	**new;
//	int		i;
//	int		j;
//
//	i = spe_count_words(lst->str);
//	new = malloc(sizeof(char *) * (i + 1));
//	if (!new)
//		return (NULL);
//	j = 0;
//	while (j < i)
//	{
//		new[j] = spe_get_word(lst->str, j);
//		if (!new[j])
//			return (NULL);
//		j++;
//	}
//	new[j] = NULL;
//	if (remove_quotes(new) != -1)
//		return (new);
//	return (NULL);
//}

char **ft_splitargs(t_lst *lst)
{
	t_lst	*start_lst;
	char	**argv;
	size_t	args;
	size_t	i;

	start_lst = lst;
	args = 0;
	i = 0;
	while (lst && lst->token != 1)
	{
		if (lst->token == 0)
			args++;
		if (lst->token >= 2 && lst->token <= 5)
			lst = lst->next;
		lst = lst->next;
	}
	argv = malloc(sizeof(char**) * (args + 1));
	while (start_lst && start_lst->token != 1)
	{
		if (start_lst->token == 0)
			argv[i++] = start_lst->str;
		if (start_lst->token >= 2 && start_lst->token <= 5)
			start_lst = start_lst->next;
		start_lst = start_lst->next;
	}
	argv[i] = NULL;
	return (argv);
}
