# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jholopai <jholopai@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/18 11:45:54 by eniini            #+#    #+#              #
#    Updated: 2020/09/11 12:25:35 by jholopai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = clang

CFLAGS = -Wall -Wextra -Werror

LIBFT = -L libft/ -lft

SRC = main.c struct_manip.c get_input.c get_tetrimino.c solve_fillit.c

OBJS = $(SRC:.c=.o)

.PHONY : library all clean fclean re

library:
	cd libft && make

all : $(NAME)

$(NAME) : library
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT)

clean : 
	rm -f $(OBJS)
	cd libft && make clean

fclean : clean
	rm -f $(NAME)
	cd libft && make fclean

re : fclean all

