/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:36:33 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:36:34 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;

	if (!(s1) || !(s2))
		return (NULL);
	s_join = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!(s_join))
		return (NULL);
	ft_memcpy(s_join, s1, ft_strlen(s1));
	ft_memcpy(s_join + ft_strlen(s1), s2, ft_strlen(s2));
	return (s_join);
}

/*
ft_strjoin(2) allocates enough memory to store the contents of both user 
inputted char arrays 's1' and 's2' in 's_join', while also taking into 
considering the needed null terminator. Then, I iterate over 's1' using 
iterator var 'i', and while I have not reached the end of 's1', I copy its 
contents to 's_join'. Next, I perform a similar process for copying 's2' but
using a separate iterator var 'j'.
*/