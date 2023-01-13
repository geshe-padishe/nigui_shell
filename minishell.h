#ifndef MINISHELL_H
# define MINISHELL_H

# include "miniparsing.h"
# include "nikishell.h"
# include "dynarray.h"

char	*ft_getenvval(char *str, t_dynarray *darr, bool val_or_all, bool un_or_exp);

#endif
