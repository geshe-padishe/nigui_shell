# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/26 00:55:12 by hkhater           #+#    #+#              #
#    Updated: 2023/01/21 03:16:18 by ngenadie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g3 #-fsanitize=address -static-libsan

RM 		=	rm -rf

NAME	=	minishell

INC		=	./miniparsing.h\

SRCS	=	adv_dquote.c \
			dynarray2.c \
			dynarray.c \
			expand.c \
			ft_builtins2.c \
			ft_builtins.c \
			ft_env.c \
			ft_exec.c \
			ft_fd.c \
			ft_files.c \
			ft_mems.c \
			ft_minishell.c \
			ft_pipelines.c \
			ft_pipes.c \
			ft_print.c \
			ft_prompt.c \
			ft_redirections.c \
			ft_sig.c \
			ft_str.c \
			is.c \
			is_token.c \
			libft.c \
			libft_utils.c \
			lst.c \
			main.c \
			parsing.c \
			quotes.c \
			syntax.c \
			tokenization.c \
			niki_utils.c \
			ft_splitargs.c

OBJS 	=	${SRCS:.c=.o}

.c.o:
		${CC} ${CFLAGS} -c $< -o $(<:.c=.o)

${NAME}:	$(OBJS)
		$(CC) $(FLAGS) $(OBJS) -lreadline -o $(NAME)

all:		${NAME}

clean:		
				${RM} $(OBJS)

fclean:		clean
				${RM} ${NAME}

re:			fclean all

val:		re
		valgrind --leak-check=full --show-leak-kinds=all --suppressions=rl_ignore ./${NAME}

val2:		re
		valgrind --suppressions=rl_ignore ./${NAME}
.PHONY:		all clean fclean c.o re
