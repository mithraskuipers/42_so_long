/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fs_s.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 15:32:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/11/21 14:19:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	fs_s(va_list arg_list)
{
	char	*arg;

	arg = va_arg(arg_list, char *);
	if (!(arg))
		return (write (1, "(null)", 6));
	ft_putstr_fd(arg, 1);
	return (ft_strlen(arg));
}
