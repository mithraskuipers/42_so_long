/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/16 15:15:18 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 12:29:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*s_new;

	if (!(s) || (!(f)))
		return (NULL);
	s_new = ft_strdup(s);
	if (!(s_new))
		return (NULL);
	i = 0;
	while (s[i])
	{
		s_new[i] = (*f)(i, s[i]);
		i++;
	}
	return (s_new);
}

/*
ft_strmapi(2) starts by making a duplicate of the user inputted char const 
array 's' using ft_strdup(1) as a way to obtain a mutable array 's_new'. Next, 
for each char in the original array, I feed that char to the user inputted 
function f() and store that function's return values inside 's_new'.
*/