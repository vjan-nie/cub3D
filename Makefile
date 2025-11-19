# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjan-nie <vjan-nie@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 12:24:16 by vjan-nie          #+#    #+#              #
#    Updated: 2025/11/18 17:11:44 by vjan-nie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	cub3D

# Paths

SRC_DIR = src

INCLUDE_DIR = includes

LIBFT_DIR = libft

MINILIBX_DIR = minilibx

CORE_DIR = core

PARSER_DIR = parser

RENDER_DIR = render

OBJ_DIR = obj

# Libft

LIBFT =			$(LIBFT_DIR)/libft.a

LIBFT_INCLUDE = -I$(LIBFT_DIR)/include

# Minilibx

MINILIBX =		$(MINILIBX_DIR)/libmlx_linux.a

# Source files

SRC			=	$(SRC_DIR)/$(CORE_DIR)/cub3d.c\
				$(SRC_DIR)/$(CORE_DIR)/key_handler.c\
				$(SRC_DIR)/$(CORE_DIR)/utils.c\
				$(SRC_DIR)/$(PARSER_DIR)/map.c\
				$(SRC_DIR)/$(PARSER_DIR)/map_utils.c\
				$(SRC_DIR)/$(PARSER_DIR)/map_utils2.c\
				$(SRC_DIR)/$(PARSER_DIR)/normalize_map.c\
				$(SRC_DIR)/$(PARSER_DIR)/parse_map.c\
				$(SRC_DIR)/$(PARSER_DIR)/parse_map_utils.c\
				$(SRC_DIR)/$(PARSER_DIR)/validate_map.c\
				$(SRC_DIR)/$(RENDER_DIR)/movement.c\
				$(SRC_DIR)/$(RENDER_DIR)/move_rotate.c\
				$(SRC_DIR)/$(RENDER_DIR)/move_wasd.c\
				$(SRC_DIR)/$(RENDER_DIR)/player.c\
				$(SRC_DIR)/$(RENDER_DIR)/player_utils.c\
				$(SRC_DIR)/$(RENDER_DIR)/raycasting.c\
				$(SRC_DIR)/$(RENDER_DIR)/raycasting_utils.c\
				$(SRC_DIR)/$(RENDER_DIR)/render.c\
				$(SRC_DIR)/$(RENDER_DIR)/textures.c

# Objects

OBJ			= 	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIRS 	= 	$(OBJ_DIR)\
				$(OBJ_DIR)/core\
				$(OBJ_DIR)/parser\
				$(OBJ_DIR)/render

# Compiling rules

CC		= 	cc

CFLAGS	= 	-Wall -Wextra -Werror -O2

MINILIBX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

# Includes

INCLUDES = -I$(INCLUDE_DIR) $(LIBFT_INCLUDE) $(MINILIBX_INCLUDE)

MINILIBX_INCLUDE	= -I$(MINILIBX_DIR)
# Building commands:

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) $(OBJ) $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MINILIBX):
	@$(MAKE) -C $(MINILIBX_DIR) || true

$(OBJ_DIRS):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	@rm -rf $(OBJ_DIRS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	-@$(MAKE) -C $(MINILIBX_DIR) clean || true

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
