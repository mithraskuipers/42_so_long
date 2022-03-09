# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/03/09 19:49:21 by mikuiper      #+#    #+#                  #
#    Updated: 2022/03/09 21:52:52 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
FLAGS = -Wall -Werror -Wextra
LIB_FT = -lft -L $(FT_DIR) 
LIB_MLX = -L $(MLX_DIR) -lmlx -lm -framework OpenGL -framework AppKit
INC = -I $(INC_DIR) -I $(FT_INC) -I $(MLX_INC)

FT_DIR = ./libft
FT_INC = $(FT_DIR)/inc/
FT = $(FT_DIR)/libft.a

MLX_DIR = ./mlx
MLX_INC = $(MLX_DIR)
MLX = $(MLX_DIR)/libmlx.a

INC_LST = so_long.h
INC_DIR = ./inc/
INC_PATHS = $(addprefix $(INC_DIR), $(INC_LST))

SRCS_DIR = ./src/
SRCS_LST =	sl_main.c \
			sl_cell.c \
			sl_parser.c \
			sl_check.c \
			sl_sprites.c \
			sl_draw.c \
			sl_draw_statics.c \
			sl_draw_dynamics.c \
			sl_input.c \
			sl_exit.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LST))

DIR_OBJ = obj/
LST_OBJ = $(patsubst %.c, %.o, $(SRCS_LST))
OBJ_PATHS = $(addprefix $(DIR_OBJ), $(LST_OBJ))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(FT) $(MLX) $(DIR_OBJ) $(OBJ_PATHS)
	@$(CC) $(FLAGS) $(LIB_FT) $(LIB_MLX) $(INC) $(OBJ_PATHS) -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was compiled$(RESET)"

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o : $(SRCS_DIR)%.c $(INC_PATHS)
	@$(CC) $(FLAGS) -c $(INC) $< -o $@

$(FT):
	@echo "$(NAME): $(GREEN)Compiling $(FT)...$(RESET)"
	@$(MAKE) -sC $(FT_DIR)

$(MLX):
	@echo "$(NAME): $(GREEN)Creating $(MLX)...$(RESET)"
	@$(MAKE) -sC $(MLX_DIR)

clean:
	@$(MAKE) -sC $(FT_DIR) clean
	@$(MAKE) -sC $(MLX_DIR) clean
	@rm -rf $(DIR_OBJ)
	@echo "$(RESET)$(NAME): $(RED)deleted $(DIR_OBJ)$(RESET)"
	@echo "$(NAME): $(RED)deleted all object files$(RESET)"

fclean: clean
	@rm -f $(MLX)
	@echo "$(NAME): $(RED)deleted $(MLX)$(RESET)"
	@rm -f $(FT)
	@echo "$(NAME): $(RED)deleted $(FT)$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)deleted ./$(NAME)$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
