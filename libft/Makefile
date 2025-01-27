# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 14:11:03 by jmiccio           #+#    #+#              #
#    Updated: 2025/01/27 23:09:38 by jmiccio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	libft.a

CC			=	cc

CFILE		=	ft_split.c		\
				ft_strcmp.c		\
				ft_strdup.c		\
				ft_strlen.c		\
				ft_strncpy.c	\
				ft_strjoin.c \
				ft_strlcpy.c \
				ft_itoa.c \
				ft_strndup.c \
				get_next_line/get_next_line.c		\
				get_next_line/get_next_line_utils.c \
				ft_printf/ft_print_func.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printhexa.c \

CFILE_DIR		=	./src/

SRC				=	$(addprefix $(CFILE_DIR), $(CFILE))

INCLUDE_DIR		=	./includes/

FLAG			= -Wall -Wextra -Werror

INCLUDE			=	libft.h

OBJ				=	$(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
