/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fs_di.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 15:32:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/11/21 14:18:29 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	fs_di(va_list arg_list)
{
	int		arg;
	char	*s;
	int		len;

	arg = (unsigned long long)va_arg(arg_list, unsigned long long);
	s = ft_itoa_base(arg, 10);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free (s);
	return (len);
}
