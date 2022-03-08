/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 16:52:06 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/26 18:07:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_uc;

	i = 0;
	s_uc = (char *)s;
	while (s_uc[i])
	{
		if (s_uc[i] == (char)c)
			return (&s_uc[i]);
		i++;
	}
	if (s_uc[i] == (char)c)
		return (&s_uc[i]);
	return (NULL);
}

/*
ft_strchr(2) typecasts the user-specified const char array 's' to be mutable,
and then iterates over each char in the array until it has found a match with 
the the desired char 'c', of which you want to find the position in 's'. If a 
match is found, return the address of the char in 's' where you found 'c'. If
at the end of 's' there still has been found no match, check then if the user
specified NULL to be the desired char to be found.
*/