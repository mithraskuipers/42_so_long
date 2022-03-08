/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/06 12:01:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/26 17:16:31 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!(ptr))
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*
ft_calloc() allocates enough space for the 'count' objects that are of 'size'
bytes of memory. If allocation fails, it returns NULL. Using ft_bzero(), it
filles the newly allocated memory with null terminators. Finally it returns
a pointer to the newly allocated memory.
*/