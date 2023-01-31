/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:45:17 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 16:25:32 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	siginthandler(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(STDIN_FILENO, "  \b\b", 4);
	g_vrac.status = 130;
}

char	*ft_make_prompt(char *dir)
{
	char	*str;

	str = malloc(ft_strlen(dir) + 2);
	ft_strcpy(dir, str);
	ft_strcpy(" ", str + ft_strlen(dir));
	return (str);
}

char	*ft_get_dir(char *path)
{
	int	i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	i--;
	if (path[i] == '/' && path[i + 1] == '\0')
		return ("/");
	while (i >= 0)
	{
		if (path[i] == '/')
			return (path + i + 1);
		i--;
	}
	return (NULL);
}

int	ft_readline(t_dynarray *darr)
{
	char		*line;
	t_lst		*lst;
	t_tout		tout;
	pid_t		list[10000];

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (printf("exit\n"), ft_free_env(darr), 0);
		if (*line)
		{
			add_history(line);
			lst = parse(line, g_vrac.status, darr);
			dprintf(2, "lst = %p\n", lst);
			if (lst)
			{
				ft_memset(&tout, 0, sizeof(t_tout));
				tout.darr = darr;
				tout.list = list;
				ft_pipes(lst, &tout);
			}
		}
	}
	rl_clear_history();
	return (0);
}
