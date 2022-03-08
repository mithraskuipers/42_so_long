# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/14 17:20:22 by mikuiper      #+#    #+#                  #
#    Updated: 2022/03/08 15:30:23 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

DIR_INC		= ./inc/
DIR_SRC		= ./src/
DIR_LIBFT	= ./libft/
DIR_MLX		= ./mlx/

LIBFT_NAME = libft.a
INC = -I include
MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework Appkit

SRC =	sl_main.c \
		sl_cell.c \
		sl_parser.c \
		sl_check.c \
		sl_sprites.c \
		sl_draw.c \
		sl_draw_statics.c \
		sl_draw_dynamics.c \
		sl_input.c \
		sl_exit.c

SRC_FULLPATH = $(addprefix $(DIR_SRC), $(SRC))
LIBFT_FULLPATH = $(addprefix $(DIR_LIBFT), $(LIBFT_NAME))
OBJ_FULLPATH = $(SRC_FULLPATH:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(DIR_INC) -o $@ -c $?

$(NAME): $(OBJ_FULLPATH)
	make -C $(DIR_LIBFT)
	make -C $(DIR_MLX)
	$(CC) -o $(NAME) $(OBJ_FULLPATH) -I $(DIR_INC) -L $(DIR_LIBFT) -lft -L \
	$(DIR_MLX) -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

clean:
	make -C $(DIR_LIBFT) clean
	make -C $(DIR_MLX) clean
	$(RM) $(OBJ_FULLPATH)

fclean:
	make -C $(DIR_LIBFT) fclean
	make -C $(DIR_MLX) fclean
	$(RM) $(NAME) $(OBJ_FULLPATH)

re: fclean all

PHONY: all clean fclean re
