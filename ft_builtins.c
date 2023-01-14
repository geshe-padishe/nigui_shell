#include "minishell.h"

int	ft_cd(char **str, int nb_pipes)
{
	struct stat stats;

	if (!*str)
		return (0);
	if (stat(*str, &stats))
		return (perror("cd"), -1);
	if (!S_ISDIR(stats.st_mode))
		return (perror("cd"), -1);
	if (nb_pipes)
		return (0);
	else if (chdir(*str) == -1)
		return (perror("cd"), -1);
	return (0);

}

int	ft_unset(t_dynarray *darr, char **str, int nb_pipes)
{
	int		index;
	char	**envp;

	if (nb_pipes > 0)
		return (0);
	while (str)
	{
		envp = darr->list;
		index = ft_getenv_index(envp, darr->nb_cells, *str, 0);
		if (index != -1)
		{
			free(envp[index]);
			dynarray_extract(darr, index, 1);
			return (0);
		}
		str++;
	}
	return (1);
}

int	ft_export(t_dynarray *darr, char **str, int nb_pipes)
{
	int	index;
	char	**envp;
	char	*envpi;

	if (nb_pipes > 0)
		return (0);
	while (str && *str)
	{
		envp = darr->list;
		if (!ft_can_exp(*str))
			return (0);
		index = ft_getenv_index(envp, darr->nb_cells, *str, 1);
		envpi = malloc(ft_strlen(*str) + 1);
		if (!envpi)
			return (perror("malloc\n"), 1);
		ft_strcpy(*str, envpi);
		if (index >= 0)
		{
			free(envp[index]);
			envp[index] = envpi;
		}
		else if (index == -1)
			if (push_dynarray(darr, &envpi, 1, 1))
				return (perror("push_dynarray"), 1);
		str++;
	}
	return (0);
}

int	ft_pwd(char **args)
{
	char	pwd[1064];

	(void)args;
	if (getcwd(pwd, 1064) == NULL)
		return (perror("pwd"), 1);
	else
		printf("%s\n", pwd);
	return (0);
}

int ft_echo(char **args)
{
	int	i;
	bool	flag;

	i = 0;
	flag = 0;
	if (args && args[0])
	{
		if (!ft_strcmp(args[0], "-n"))
		{
			i++;
			flag = 1;
		}
		while (args[i])
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			i++;
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}
