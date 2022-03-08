/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fs_u.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 15:32:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/11/19 15:41:49 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	fs_u(va_list arg_list)
{
	unsigned int	arg;
	char			*s;
	int				len;

	arg = va_arg(arg_list, unsigned int);
	s = ft_utoa_base(arg, 10);
	ft_putstr_fd(s, 1);
	len = ft_strlen(s);
	free (s);
	return (len);
}
