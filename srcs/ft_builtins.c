#include "minishell.h"

int	ft_cd(char **str, char *home)
{
	if (!str)
	{
		if (home)
			chdir(home);
		else
			return (perror("cd: HOME not set\n"), -1);
	}
	else if (*str && chdir(*str) == -1)
		return (perror("cd: Invalid Path\n"), -1);
	return (0);

}

int	ft_unset(t_dynarray *darr, char **str)
{
	int	index;
	char	**envp;

	while (str)
	{
		envp = darr->list;
		index = ft_getenv_index(envp, darr->nb_cells, *str, 0);
		if (index != -1)
		{
			free(envp[index]);
			dynarray_extract(darr, index, 1);
		}
		str++;
	}
	return (0);
}

int	ft_export(t_dynarray *darr, char **str)
{
	int	index;
	char	**envp;
	char	*envpi;

	while (str)
	{
		envp = darr->list;
		if (!ft_has_eq(*str))
			return (0);
		index = ft_getenv_index(envp, darr->nb_cells, *str, 1);
		envpi = malloc(ft_strlen(*str) + 1);
		ft_strcpy(*str, envpi);
		if (index >= 0)
		{
			free(envp[index]);
			envp[index] = envpi;
		}
		else if (index == -1)
			push_dynarray(darr, &envpi, 1, 0);
		str++;
	}
	return (0);
}

void	ft_pwd(char **args)
{
	char	*pwd;

	if (args != NULL)
	{
		perror("pwd: too many arguments\n");
		return ;
	}
	pwd = NULL;
	if (!getcwd(pwd, 1000))
		perror("getcwd: Unable to retrieve path\n");
	else
		printf("%s\n", pwd);
}

void	ft_echo(char **args)
{
	int	i;
	bool	flag;

	i = 0;
	flag = 0;
	if (args && args[0])
	{
		if (ft_strcmp(args[0], "-n"))
		{
				flag = 1;
				i++;
		}
		while (args[i])
		{
				printf("%s", args[i]);
				i++;
		}
	}
	if (!flag)
		printf("\n");
}
