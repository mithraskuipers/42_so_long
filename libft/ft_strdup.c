/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 19:42:41 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 10:10:11 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!(dup))
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// CALLOC ()

/*
ft_strdup(1) uses ft_strlen(1) to sufficient memory such that it can store the
inputted char array 's1' in a new array 'dup'. Then, it iterates over each char
in 's1' and stores that char in 'dup'. Finally, it adds a null terminator to 
'dup'.
*/