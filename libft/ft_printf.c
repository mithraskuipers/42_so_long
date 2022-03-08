/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 10:22:54 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 13:41:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	parse_format(char fs_char, va_list arg_list)
{
	int	nchars;

	nchars = 0;
	if (fs_char == 'c')
		nchars = (nchars + fs_c(arg_list));
	else if (fs_char == 's')
		nchars = (nchars + fs_s(arg_list));
	else if (fs_char == 'p')
		nchars = (nchars + fs_p(arg_list));
	else if ((fs_char == 'd') || (fs_char == 'i'))
		nchars = (nchars + fs_di(arg_list));
	else if (fs_char == 'u')
		nchars = (nchars + fs_u(arg_list));
	else if (fs_char == 'x')
		nchars = (nchars + fs_x(arg_list));
	else if (fs_char == 'X')
		nchars = (nchars + fs_x_upper(arg_list));
	else if (fs_char == '%')
		nchars = (nchars + write(1, "%", 1));
	else if (fs_char != '\0')
		return (write(1, &fs_char, 1));
	return (nchars);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_list;
	int		i;
	int		nchars;
	char	*format_s;

	va_start(arg_list, format);
	i = 0;
	nchars = 0;
	format_s = (char *)format;
	while (format_s[i])
	{
		if (format_s[i] == '%')
		{
			nchars = nchars + parse_format(format_s[i + 1], arg_list);
			if (format_s[i + 1] != '\0')
				i++;
		}
		else
			nchars = (nchars + write(1, &format_s[i], 1));
		i++;
	}
	va_end(arg_list);
	return (nchars);
}
