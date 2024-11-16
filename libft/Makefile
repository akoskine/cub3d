# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 16:37:08 by akoskine          #+#    #+#              #
#    Updated: 2023/09/06 16:38:14 by akoskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar.c \
ft_putchar_fd.c \
ft_putendl.c \
ft_putendl_fd.c \
ft_putnbr.c \
ft_putnbr_fd.c \
ft_putstr.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strcmp.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strndup.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_free_str.c \
get_next_line.c \
get_next_line_utils.c

NAME = libft.a
FT_PRINTF = ./ft_printf/libftprintf.a
OF = ${LIBFT:.c=.o}

all: $(NAME)

$(NAME) : $(LIBFT) $(FT_PRINTF)
	cc -Wall -Wextra -Werror -c $(LIBFT)
	ar rcs $(NAME) $(OF)

$(FT_PRINTF) :
	make -C ./ft_printf


clean:
	rm -rf $(OF)
	make clean -C ./ft_printf

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./ft_printf

re: fclean all
