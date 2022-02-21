# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mikuiper <mikuiper@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/21 15:18:55 by mikuiper      #+#    #+#                  #
#    Updated: 2022/02/21 15:18:56 by mikuiper      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NOCOLOR = \033[0m
GREEN = \033[92m
YELLOW= \033[93m

NAME = libftprintf.a

ODIR = objects
SDIR = srcs

# Parent folder.
_SRCS = ft_printf.c \
		ft_checkflag.c \
		ft_checkformat.c \
		ft_hex_convert.c \
		ft_hex_convert_pointer.c \
		ft_itoa_long.c \
		ft_printing.c \
		ft_putchar_fd_return.c \
		ft_putnbr_fd_return.c \
		ft_putnbr_fd_unsigned.c \
		ft_putstr_fd_return.c \
		ft_structset.c \
		ft_putchar_flags.c \
		ft_putnbr_flags.c \
		ft_putnbr_flags_negative.c \
		ft_putnbr_flags_print.c \
		ft_putnbr_print_pointer.c \
		ft_putstr_flags.c

_OFILES := $(_SRCS:.c=.o)

SRCS = $(addprefix $(SDIR)/, $(_SRCS))
OFILES = $(addprefix $(ODIR)/, $(_OFILES))

HEADER = printf.h

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OFILES)
	@echo "$(YELLOW)[ft_printf] - Compiling libft.$(NOCOLOR)"
	@$(MAKE) -C libft
	@mv libft/libft.a $(NAME)
	@echo "$(YELLOW)[ft_printf] - Merging libft.a with libftprintf.a$(NOCOLOR)"
	@ar rcs $(NAME) $(OFILES)
	@echo "$(YELLOW)[ft_printf] - Created libftprintf.a and moved \
	objects files to the objects directory.$(NOCOLOR)"

$(ODIR)/%.o: $(SDIR)/%.c $(HEADER)
	@mkdir -p $(ODIR)
	gcc -Wall -Wextra -Werror -c $< -o $@ -I

clean:
	@/bin/rm -f a.out
	@$(MAKE) -C libft clean
	@echo "$(YELLOW)[ft_printf] - Removed All Object Files.$(NOCOLOR)"

fclean:    clean
	@/bin/rm -rf $(ODIR)
	@/bin/rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "$(YELLOW)[ft_printf] - Removed .a file and all .o files.$(NOCOLOR)"

re: fclean all
	@/bin/rm -f $(OFILES)

compile: all
	gcc $(NAME) main.c && ./a.out