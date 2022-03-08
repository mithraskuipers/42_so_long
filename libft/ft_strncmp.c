/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 10:29:20 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/27 23:10:14 by mkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	i = 0;
	s1_uc = (unsigned char *)s1;
	s2_uc = (unsigned char *)s2;
	while (i < n)
	{
		if ((!s1_uc[i]) && (s1_uc[i] == s2_uc[i]))
			return (0);
		if (s1_uc[i] != s2_uc[i])
			return (s1_uc[i] - s2_uc[i]);
		i++;
	}
	return (0);
}

/*
ft_strncmp(3) compares the char arrays 's1' and 's2' for no more than 'n' chars
and returns the ascii difference between the chars where 's1' and 's2' deviate 
from eachother. For each char in both 's1' and 's2' a comparsion is made, and 
when the current chars of both arrays deviates, the char of 's2' is subtracted
from the char of 's1' and returned. If I reached the end of 's1' and the last
chars of 's1' and 's2' are equal to eachother, ft_strncmp(3) returns 0.
*/