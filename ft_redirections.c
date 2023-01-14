#include "minishell.h"

int	ft_handle_redirections(t_lst *lst)
{
	while (lst && lst->token != 1)
	{
		if (lst->token == 2 || lst->token == 3 || lst->token == 4)
		{
			if (ft_open_dup(lst, lst->token, 0) == -1)
				return (-1);
			lst = lst->next;
		}
		lst = lst->next;
	}
	return (0);
}

int	ft_open_dup(t_lst *lst, int token, bool apnd_or_not)
{
	int	fd;

	fd = -1;
	if (token == 2 || token == 4)
	{
		if (token == 4)
			apnd_or_not = 1;
		//dprintf(2, "DUP2 token %d\n", token);
		fd = ft_open_create(lst->next->str, apnd_or_not, token);
		if (fd != -1 && dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), perror("dup"), -1);
		close(fd);
	}
	else
	{
		//dprintf(2, "DUP2 token 3\n");
		fd = ft_open_create(lst->next->str, 0, token);
		if (fd != -1 && dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), perror("dup"), -1);
	}
	if (fd != -1)
		close(fd);
	return (fd);
}
