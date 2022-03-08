/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 19:57:23 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/26 22:26:48 by mkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;
	size_t	s_len;

	if (!(s))
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	s_len = (ft_strlen(s) - start);
	if (s_len < len)
		len = s_len;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!(sub_s))
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[(start + i)];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}

/*
ft_substr(3) start by checking whether the user specified a char array 's', and 
returns NULL otherwise. Next, it checks if the specified start index is actually
smaller than the length of 's', and otherwise it returns an empty char array
using ft_strdup(1). Then it determines the length of the desired substring
by subtracting the length of 's' by that of the user specified length 'len'. If
the length of 's' is smaller than 'len', len is set to be the length of 's'.
Following, ft_substr(3) allocates the required amount of memory for 'sub_s' and 
checks whether the allocation succeeded. Now the desired section of 's' is
copied over to 'sub_s' in an iterative manner. Finally, 'sub_s' receives a null
terminator and is returned by ft_substr(3).
*/
