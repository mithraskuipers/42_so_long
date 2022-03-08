/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/07 17:21:40 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/26 18:15:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*s_uc;

	len = ft_strlen((char *)s);
	s_uc = (char *)s;
	while ((len != '\0') && (s_uc[len] != (char)c))
		len--;
	if (s_uc[len] == (char)c)
		return (&s_uc[len]);
	return (NULL);
}

/*
ft_strrchr(2) typecasts the user-specified const char array 's' to be mutable,
and then iterates over each char in the array in a backwards manner for as long
as no match has been found with 'c'. If a match is found, return the address of 
the char in 's' where you found 'c'.
*/