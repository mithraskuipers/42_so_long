/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 17:11:07 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/27 19:27:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_i;
	size_t	needle_i;

	if (!(*needle))
		return ((char *)haystack);
	haystack_i = 0;
	while ((haystack[haystack_i]) && (haystack_i < len))
	{
		needle_i = 0;
		if (haystack[haystack_i] == needle[needle_i])
		{
			needle_i++;
			while ((needle[needle_i]) && \
			(haystack[haystack_i + needle_i] == needle[needle_i]) && \
			((haystack_i + needle_i) < len))
				needle_i++;
			if (!(needle[needle_i]))
				return ((char *)&haystack[haystack_i]);
		}
		haystack_i++;
	}
	return (0);
}

/*
The main approach of my ft_strnstr(3) is by iterating over the char array 
'haystack' and then checking whether the current char is equal to the first
char of the char array 'needle'. If there is a match, I start comparing both
array on a char by char basis until I reached the end of 'needle'. If that
happens, I know that the entirety of 'needle' was hidden inside 'haystack' I 
return a pointer to the first char of the first occurrence of 'needle'
*/