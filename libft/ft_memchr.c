/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 14:53:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 08:49:17 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_uc;
	unsigned char	c_uc;
	size_t			i;

	i = 0;
	s_uc = (unsigned char *)s;
	c_uc = (unsigned char)c;
	while (i < n)
	{
		if (s_uc[i] == c_uc)
			return (&(s_uc[i]));
		i++;
	}
	return (NULL);
}
