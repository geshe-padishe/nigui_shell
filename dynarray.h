/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynarray.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikotikcho <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:19:38 by nikotikch         #+#    #+#             */
/*   Updated: 2023/01/13 20:43:30 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNARRAY_H
# define DYNARRAY_H

# include "common.h"

int		init_dynarray(t_dynarray *dynarray,
			uint64_t nb_cells, size_t cell_size);
void	clear_dynarray(t_dynarray *dynarray);
void	free_dynarray(t_dynarray *dynarray);
int		pop_dynarray(t_dynarray *dynarray, uint64_t nb_cells_pop, bool way);
int		push_dynarray(t_dynarray *dynarray, void *new_cells,
			uint64_t nb_ncells, bool way);
int		dynarray_realloc(t_dynarray *dynarray, size_t new_byte_size);
int		dynarray_extract(t_dynarray *darr, uint64_t index, uint64_t nb_ext);
int		dyn_insr(t_dynarray *darr, void *ncells,
			uint64_t index, uint64_t nb_ncells);
void	*dynacc(t_dynarray *darr, uint64_t index);
size_t	ft_strlen(const char *str);
int		ft_strcpy(char *str, char *str2);
int		ft_strncpy(char *str, char *str2, int n);

#endif
