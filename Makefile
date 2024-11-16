# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 22:49:25 by akoskine          #+#    #+#              #
#    Updated: 2024/11/16 16:53:21 by akoskine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all re clean fclean bonus

# Program file name
NAME	= cub3D

# Compiler and compilation flags
CC		= cc
CFLAGS	= -Werror -Wextra -Wall #-fsanitize=address

# Minilibx
MLX_PATH	= ./mlx/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Sources
SRC_PATH = ./sources/
SRC	=	main.c \
		draw.c \
		utils.c \
		update.c \
		dda.c \
		door.c \
		door_utils.c \
		draw_utils.c \
		dmh.c \
		minimap.c \
		parse_and_init_utils.c \
		parse_and_init.c \
		map_creation.c \
		map_information.c \
		map_validation.c \
		hud.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= ./objects/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# Includes
INC			=	-I ./includes/\
				-I ./libft/\
				-I ./lmx/

# Main rule
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# Objects rule
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Project file rule
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX) -framework OpenGL -framework AppKit -lbsd -lmlx lXext -lX11

# Libft rule
$(LIBFT):
	make -sC $(LIBFT_PATH)

# MLX rule
$(MLX):
	make -sC $(MLX_PATH)

# Clean up build files rule
clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

# Remove program executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

# Clean + remove executable
re: fclean all