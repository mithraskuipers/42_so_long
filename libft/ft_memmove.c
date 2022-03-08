/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 16:03:41 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 08:46:46 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_uc;
	unsigned const char	*src_uc;

	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned const char *)src;
	if ((dst == NULL) && (src == NULL) && (len > 0))
		return (dst_uc);
	else if (dst_uc < src_uc)
		ft_memcpy(dst_uc, src_uc, len);
	else
	{
		while (len)
		{
			dst_uc[(len - 1)] = src_uc[(len - 1)];
			len--;
		}
	}
	return (dst);
}
