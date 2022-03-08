/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_countlines_fd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/16 12:25:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/01/16 12:28:38 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countlines_fd(int fd)
{
	char	buff[1];
	int		count;
	int		nbytes;

	buff[0] = '\0';
	nbytes = 1;
	count = 0;
	while(nbytes)
	{
		nbytes = read(fd, buff, 1);
		if(ft_strchr(buff, '\n') || ft_strchr(buff, '\0'))
		{
			count++;
		}
	}
	return (count);
}