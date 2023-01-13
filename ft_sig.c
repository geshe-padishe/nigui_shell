#include "minishell.h"

void	sigd_handler1(int i)
{
	(void)i;
	write(1, "\n> ", 3);
}

void	sigd_handler2(int i)
{
	(void)i;
	write(1, "\b\b  \b\b", 6);
}
