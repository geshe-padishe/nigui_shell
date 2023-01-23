#include "minishell.h"

int	ft_cd(char **str)
{
	struct stat	stats;

	printf("inside cd\n");
	if (!*str)
		return (free(str - 1), 1);
	if (stat(*str, &stats))
		return (free(str - 1), perror("cd"), 1);
	if (!S_ISDIR(stats.st_mode))
		return (free(str - 1), perror("cd"), 1);
	else if (chdir(*str) == -1)
		return (free(str - 1), perror("cd"), 1);
	return (free(str - 1), 0);

}

int	ft_unset(t_dynarray *darr, char **str)
{
	int		index;
	char	**envp;
	int		i;

	i = 0;
	while (str && str[i])
	{
		envp = darr->list;
		index = ft_getenv_index(envp, darr->nb_cells, str[i], 0);
		if (index != -1)
		{
			free(envp[index]);
			dynarray_extract(darr, index, 1);
		}
		i++;
	}
	return (free(str - 1), 0);
}

int	ft_export(t_dynarray *darr, char **str)
{
	int		index;
	char	**envp;
	char	*envpi;
	int		i;

	i = 0;
	while (str && str[i])
	{
		envp = darr->list;
		if (!ft_can_exp(str[i]))
			return (free(str - 1), 1);
		index = ft_getenv_index(envp, darr->nb_cells, str[i], 1);
		envpi = malloc(ft_strlen(str[i]) + 1);
		if (!envpi)
			return (free(str - 1), perror("malloc\n"), 1);
		ft_strcpy(str[i], envpi);
		if (index >= 0)
		{
			free(envp[index]);
			envp[index] = envpi;
		}
		else if (index == -1)
			if (push_dynarray(darr, &envpi, 1, 1))
				return (free(str - 1), perror("push_dynarray"), 1);
		i++;
	}
	return (/* free(str - 1),*/ 0);
}

int	ft_pwd(char **args)
{
	char	pwd[1064];

	dprintf(2, "INSIDE PWD\n");
	if (getcwd(pwd, 1064) == NULL)
		return (free(args - 1), perror("pwd"), 1);
	return (printf("%s\n", pwd), free(args - 1), 0);
}

int ft_echo(char **args)
{
	int		i;
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
	return (free(args - 1), 1);
}
