/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fs_x.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 15:17:02 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 13:41:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	fs_x(va_list arg_list)
{
	unsigned int	arg;
	char			*s;
	int				len;

	arg = ((unsigned int)va_arg(arg_list, int));
	s = ft_itoa_base(arg, 16);
	ft_putstr_fd(s, 1);
	len = ft_strlen(s);
	free (s);
	return (len);
}

int	fs_x_upper(va_list arg_list)
{
	unsigned int	arg;
	char			*s;
	int				len;

	arg = ((unsigned int)va_arg(arg_list, int));
	s = ft_itoa_base(arg, 16);
	s = ft_stoupper(s);
	ft_putstr_fd(s, 1);
	len = ft_strlen(s);
	free (s);
	return (len);
}
