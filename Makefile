#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 12:55:59 by msakovyc          #+#    #+#              #
#    Updated: 2018/06/17 12:56:01 by msakovyc         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem-in
SRCS = main.c validation.c ways_help.c find_ways.c solution.c solv_help.c
FLAGS = -Wall -Werror -Wextra
# -g -fsanitize=address

all: $(NAME) 

$(NAME): $(SRCS)
	@ make -C libft re
	@ gcc $(FLAGS) $(SRCS) libft/libft.a -o $(NAME)

%.o:%.c
	@ gcc -c $< -o $@ $(FLAGS)

clean:
	@ make -C libft clean

fclean: clean
	@ rm -f $(NAME)
	@ make -C libft fclean

re: fclean all
