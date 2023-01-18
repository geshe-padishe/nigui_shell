#include "minishell.h"

int	ft_cd(char **str)
{
	struct stat stats;

	if (!*str)
		return (free(str - 1), -3);
	if (stat(*str, &stats))
		return (free(str - 1), perror("cd"), -2);
	if (!S_ISDIR(stats.st_mode))
		return (free(str - 1), perror("cd"), -2);
	if (nb_pipes)
		return (free(str - 1), -3);
	else if (chdir(*str) == -1)
		return (free(str - 1), perror("cd"), -2);
	return (free(str - 1), -3);

}

int	ft_unset(t_dynarray *darr, char **str)
{
	int		index;
	char	**envp;

	if (nb_pipes > 0)
		return (free(str - 1), 0);
	while (str && *str)
	{
		envp = darr->list;
		index = ft_getenv_index(envp, darr->nb_cells, *str, 0);
		if (index != -1)
		{
			free(envp[index]);
			dynarray_extract(darr, index, 1);
			return (free(str - 1), 0);
		}
		str++;
	}
	return (free(str - 1), 0);
}

int	ft_export(t_dynarray *darr, char **str)
{
	int	index;
	char	**envp;
	char	*envpi;

	if (nb_pipes > 0)
		return (free(str - 1), -3);
	while (str && *str)
	{
		envp = darr->list;
		if (!ft_can_exp(*str))
			return (free(str - 1), -3);
		index = ft_getenv_index(envp, darr->nb_cells, *str, 1);
		envpi = malloc(ft_strlen(*str) + 1);
		if (!envpi)
			return (free(str - 1), perror("malloc\n"), -2);
		ft_strcpy(*str, envpi);
		if (index >= 0)
		{
			free(envp[index]);
			envp[index] = envpi;
		}
		else if (index == -1)
			if (push_dynarray(darr, &envpi, 1, 1))
				return (free(str - 1), perror("push_dynarray"), -2);
		str++;
	}
	return (printf("export end\n"), free(str - 1), -3);
}

int	ft_pwd(char **args)
{
	char	pwd[1064];

	if (getcwd(pwd, 1064) == NULL)
		return (free(args - 1), perror("pwd"), 1);
	return (printf("%s\n", pwd), free(args - 1), 0);
}

int ft_echo(char **args)
{
	int	i;
	bool	flag;
	bool	flags_ended;
	int		is_flag;

	i = 0;
	flag = 0;
	flags_ended = 0;
	if (args && args[0])
	{
		while (args[i])
		{
			is_flag = ft_is_flag(args[i]);
			if (is_flag == 0)
				flags_ended = 1;
			else
				flag = 1;
			if (flags_ended)
			{
				printf("%s", args[i]);
				if (args[i + 1])
					printf(" ");
			}
			i++;
		}
	}
	if (!flag)
		printf("\n");
	return (free(args - 1), 0);
}
