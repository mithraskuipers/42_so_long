/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/16 12:25:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/01/16 12:28:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_fd(int fd)
{
	char	buff[1];
	int		len;
	int		nbytes;

	buff[0] = '\0';
	nbytes = 1;
	len = 0;
	while(nbytes)
	{
		nbytes = read(fd, buff, 1);
		if (buff[0] != '\n')
		{
			len++;
		}
		else
		{
			break;
		}
	}
	return (len);
}