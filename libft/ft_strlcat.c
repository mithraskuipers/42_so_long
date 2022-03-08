/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 07:52:37 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/27 23:27:59 by mkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{	
	size_t	dst_len;
	size_t	src_len;

	dst_len = 0;
	src_len = 0;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	while ((src[src_len]) && ((dst_len + src_len + 1) < dstsize))
	{
		dst[dst_len + src_len] = src[src_len];
		src_len++;
	}
	if (dst_len != dstsize)
		dst[dst_len + src_len] = '\0';
	return (dst_len + ft_strlen(src));
}
