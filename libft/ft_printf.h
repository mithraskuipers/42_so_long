/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 13:42:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 13:43:44 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include "libft.h"

/* ft_printf */
int		ft_printf(const char *fs_list, ...);
int		parse_fs_list(char fs_char, va_list arg_list);
int		fs_c(va_list arg_list);
int		fs_s(va_list arg_list);
int		fs_p(va_list arg_list);
int		fs_di(va_list arg_list);
int		fs_u(va_list arg_list);
int		fs_x(va_list arg_list);
int		fs_x_upper(va_list arg_list);

/* libft */
size_t	ft_strlen(const char *s);
char	*ft_itoa_base(long long n, int base);
char	*ft_utoa_base(unsigned long long n, int base);
char	*ft_stoupper(char *s);
void	ft_putstr_fd(char *s, int fd);

#endif