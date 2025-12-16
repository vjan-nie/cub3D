# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sergio-jimenez <sergio-jimenez@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 12:24:16 by vjan-nie          #+#    #+#              #
#    Updated: 2025/12/16 18:08:01 by sergio-jime      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Project

NAME			=	cub3D

# **************************************************************************** #
# Paths

SRC_DIR			=	src
INCLUDE_DIR		=	includes
LIBFT_DIR		=	libft
MINILIBX_DIR	=	minilibx
CORE_DIR		=	core
PARSER_DIR		=	parser
RENDER_DIR		=	render
OBJ_DIR			=	obj

# **************************************************************************** #
# Libft

LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDE	=	-I$(LIBFT_DIR)/include

# **************************************************************************** #
# Minilibx

MINILIBX		=	$(MINILIBX_DIR)/libmlx_linux.a
MINILIBX_INCLUDE=	-I$(MINILIBX_DIR)

# **************************************************************************** #
# Source files

SRC				=	$(SRC_DIR)/$(CORE_DIR)/cub3d.c\
					$(SRC_DIR)/$(CORE_DIR)/key_handler.c\
					$(SRC_DIR)/$(CORE_DIR)/utils.c\
					$(SRC_DIR)/$(CORE_DIR)/cleaner.c\
					$(SRC_DIR)/$(PARSER_DIR)/map.c\
					$(SRC_DIR)/$(PARSER_DIR)/map_utils.c\
					$(SRC_DIR)/$(PARSER_DIR)/map_utils2.c\
					$(SRC_DIR)/$(PARSER_DIR)/map_utils3.c\
					$(SRC_DIR)/$(PARSER_DIR)/normalize_map.c\
					$(SRC_DIR)/$(PARSER_DIR)/parse_map.c\
					$(SRC_DIR)/$(PARSER_DIR)/parse_map_utils.c\
					$(SRC_DIR)/$(PARSER_DIR)/parse_map_utils2.c\
					$(SRC_DIR)/$(PARSER_DIR)/parse_map_aux.c\
					$(SRC_DIR)/$(PARSER_DIR)/validate_map.c\
					$(SRC_DIR)/$(RENDER_DIR)/movement.c\
					$(SRC_DIR)/$(RENDER_DIR)/move_rotate.c\
					$(SRC_DIR)/$(RENDER_DIR)/move_wasd.c\
					$(SRC_DIR)/$(RENDER_DIR)/player.c\
					$(SRC_DIR)/$(RENDER_DIR)/player_utils.c\
					$(SRC_DIR)/$(RENDER_DIR)/raycasting.c\
					$(SRC_DIR)/$(RENDER_DIR)/raycasting_utils.c\
					$(SRC_DIR)/$(RENDER_DIR)/raycasting_utils2.c\
					$(SRC_DIR)/$(RENDER_DIR)/render.c\
					$(SRC_DIR)/$(RENDER_DIR)/textures.c

# **************************************************************************** #
# Objects

OBJ				=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIRS		=	$(OBJ_DIR)\
					$(OBJ_DIR)/core\
					$(OBJ_DIR)/parser\
					$(OBJ_DIR)/render

# **************************************************************************** #
# Compiling rules

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O2 -g
MINILIBX_FLAGS	=	-L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

# **************************************************************************** #
# Includes

INCLUDES		=	-I$(INCLUDE_DIR) $(LIBFT_INCLUDE) $(MINILIBX_INCLUDE)

# **************************************************************************** #
# Colors

GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
RESET			=	\033[0m

# Building commands:

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) $(OBJ) $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

$(MINILIBX):
	@echo "$(YELLOW)Compiling minilibx...$(RESET)"
	@$(MAKE) -s -C $(MINILIBX_DIR) || true
	@echo "$(GREEN)✓ minilibx compiled!$(RESET)"

$(OBJ_DIRS):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIRS)
	@printf "$(BLUE)Compiling $<...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MINILIBX_INCLUDE) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIRS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	-@$(MAKE) -s -C $(MINILIBX_DIR) clean || true
	@echo "$(GREEN)✓ Clean complete!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✓ Full clean complete!$(RESET)"

re: fclean all
	@printf "$(YELLOW)Rebuild completed$(RESET)\n"

.PHONY: all clean fclean re
