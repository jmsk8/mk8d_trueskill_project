# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 17:16:04 by jmiccio           #+#    #+#              #
#    Updated: 2025/02/05 16:01:43 by jmiccio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mk8d_trueskill

SRC_DIR = ./src/

C_FILES =	main.c \
			set.c \
			utils.c \
			read.c \
			lst_utils.c \
			player_struct.c \
			parsing.c \
			exec.c \
			signals.c \
			true_skill.c \
			true_skill_utils.c \
			prepare_tournament.c \
			display.c \
			commands.c

SRC = $(addprefix $(SRC_DIR), $(C_FILES))
OBJ = $(SRC:.c=.o)

INCLUDE = -I includes
LIBFT = libft/libft.a 
CFLAGS = -Wall -Werror -Wextra $(INCLUDE) -L -lft -I/usr/include/readline

LDFLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	$(CC) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

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
