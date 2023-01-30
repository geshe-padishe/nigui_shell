/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:55 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/29 15:47:14 by nvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIPARSING_H
# define MINIPARSING_H

# include "dynarray.h"

# define SYNTAX_ERR "bash: syntax error near unexpected token `"

// Parsing.c
t_lst	*parse(char *line, int ext, t_dynarray *darr);

// Quotes.c
int		var_name_len(char *str);
char	*protect_content(char *str, int rev);
char	*dup_quote(char *s);

// Heredoc.c
char	*heredoc(char *line);

// Syntax.c
int		syntax_check(char *line);

// is.c
int		ft_isdigit(int c);
int		is_alnumund(int c);
int		is_redir(char c);
int		is_operator(char c);
int		is_sep(char c);

// Expand.c
char	*trio_merge(char *before, char *value, char *after);
char	*my_expand(char *str, int ext, t_dynarray *darr);

// Libft.c + Libft_utils.c
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);
size_t	unquote_len(const char *str);
char	*ft_free(char *str1, char *str2, char *str3, char *str4);

// is_token.c
int		is_space(char c);
int		is_quote(char c);
int		has_quote(char *str);
int		recognize_op(char *str);

// Tokenization
t_lst	*tokenize(char *line);

// Lst.c
t_lst	*first_lst(t_lst *lst);
void	free_lst(t_lst *src);
void	push_lst(t_lst *neww, t_lst *lst);
char	*put_err(char *str);
int		lst_len(t_lst *lst);
t_lst	*new_lst(void);
void	push_first_lst(t_lst *neww, t_lst *lst);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
