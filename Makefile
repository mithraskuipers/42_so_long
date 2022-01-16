# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/14 17:20:22 by mikuiper      #+#    #+#                  #
#    Updated: 2022/01/16 13:14:31 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
NAME_BONUS	= so_long_bonus

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

DIR_INC		= ./inc/
DIR_SRC		= ./src/
DIR_LIBFT	= ./libftplusplus/
DIR_MLX		= ./mlx/

DIR_INC_BONUS = ./include_bonus/
DIR_SRC_BONUS = ./src_bonus/

LIBFT_NAME = libft.a
INC = -I include
MLX_FLAGS = -L./mlx -lmlx -framework OpenGL -framework Appkit

SRC =	main.c
SRC_BONUS = main_bonus.c

SRC_FULLPATH = $(addprefix $(DIR_SRC), $(SRC))
LIBFT_FULLPATH = $(addprefix $(DIR_LIBFT), $(LIBFT_NAME))
OBJ_FULLPATH = $(SRC_FULLPATH:.c=.o)

SRC_BONUS_FULLPATH = $(addprefix $(SRCS_BONUS_DIR), $(SRC_BONUS))
OBJ_BONUS_FULLPATH = $(SRC_BONUS_FULLMATH:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(DIR_INC) -o $@ -c $?

$(NAME): $(OBJ_FULLPATH)
	make -C $(DIR_LIBFT) plusplus
	make -C $(DIR_MLX)
	$(CC) -o $(NAME) $(OBJ_FULLPATH) -I $(DIR_INC) -L $(DIR_LIBFT) -lft -L $(DIR_MLX) -lmlx -framework OpenGL -framework Appkit

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS_FULLPATH)
	make -C $(DIR_LIBFT) plusplus
	make -C $(DIR_MLX)
	$(CC) -o $(NAME_BONUS) $(OBJ_BONUS_FULLPATH) -I $(DIR_INC) -L $(DIR_LIBFT) -lft -L $(DIR_MLX) -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

clean:
	#make -C $(DIR_LIBFT) clean
	#make -C $(DIR_MLX) clean
	$(RM) $(OBJ_FULLPATH) $(OBJ_BONUS_FULLPATH)

fclean:
	#make -C $(DIR_LIBFT) fclean
	#make -C $(DIR_MLX) fclean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

PHONY: all clean fclean re bon