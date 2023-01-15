#include "minishell.h"

void	sigintHandler(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	int			ret;
	t_lst		*lst;
	int			status;

	ret = 0;
	status = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			return (0);
		if (*line)
		{
			add_history(line);
			lst = parse(line, status, darr);
			if (lst)
			{
				ret = ft_pipes(lst, ft_pipes_left(lst), darr, &status);
				printf("status = %d\n", status);
				printf("ret = %d\n", ret);
				if (status == -2)
					status = 1;
				free_lst(lst);
				lst = NULL;
			if (ret >= 0)
				return (/*free(line),*/ ret);
			}
		}
		//free(line);
	}
	rl_clear_history();
	return (0);
}
