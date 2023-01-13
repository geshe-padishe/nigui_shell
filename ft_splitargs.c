#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

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
