# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 17:16:04 by jmiccio           #+#    #+#              #
#    Updated: 2025/01/27 22:53:52 by jmiccio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mk8d_trueskill

SRC_DIR = ./src/

C_FILES =	main.c \
			set.c \
			utils.c \
			read.c \
			lst_utils.c \
			player_struct.c

SRC = $(addprefix $(SRC_DIR), $(C_FILES))
OBJ = $(SRC:.c=.o)

INCLUDE = -I includes
LIBFT = libft/libft.a
CFLAGS = -Wall -Werror -Wextra $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@make clean -C libft
	rm -f $(OBJ)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean bonus re
