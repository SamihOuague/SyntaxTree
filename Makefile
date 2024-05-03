# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 03:50:57 by  souaguen         #+#    #+#              #
#    Updated: 2024/05/03 10:08:51 by souaguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Werror -Wextra -g -I./libft -I./
SRC=main.c \
    src/ft_tree.c \
    src/ft_tree_utils.c \
    src/ft_exec_tree.c
OBJ=$(SRC:.c=.o)
NAME=ast
LIBFT=./libft
LIB=libft.a

$(NAME): $(OBJ)
	make -C $(LIBFT) all bonus
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -l:$(LIB) -o $(NAME)

all: $(NAME)

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
