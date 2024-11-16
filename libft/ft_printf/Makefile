# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoskine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 16:37:08 by akoskine          #+#    #+#              #
#    Updated: 2022/12/06 17:08:04 by akoskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c ft_putchar_pf.c ft_puthex_pf.c ft_putnbr_pf.c ft_putptr_pf.c ft_putstr_pf.c ft_putunsigned_pf.c ft_writecheck_pf.c

OF = ${SRC:.c=.o}

all: $(NAME)

$(NAME):
	cc -Wall -Wextra -Werror -c $(SRC)
	ar rcs $(NAME) $(OF)

clean:
	rm -rf $(OF)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
