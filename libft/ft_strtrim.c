/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:36:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:36:52 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	if ((!(s1)) || (!(set)))
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (ft_isinset(s1[i], set))
		i++;
	if (!(j > i))
		return (ft_strdup(""));
	while (ft_isinset(s1[j - 1], set))
		j--;
	return (ft_substr(s1, i, (j - i)));
}

/*
ft_strtrim(2) makes use of a helper function ft_isinset(2) that simply checks
whether the inputted char occurs in the inputted set of chars 'set'. Here, that
function helps out greatly, since it allows me to iterate over each char of the
char array 's1' and feed each char to ft_isinset(2). If the helper function
returns 1, it means that indeed the current char occurs in 'set', and 0 
otherwise. Now, what ft_strtrim(2) does it iterate over each char in 's1' and
feed that to ft_isinset(2) and as long as that returns 1, I keep iterating over
's1' using iterator var 'i' in a forward going manner informing me that I can 
'trim' these chars from the left side of 's1'. Next, I check whether I the 
length 's1' is not greater than my iterator var, which would mean that I reached
the end of 's1' and that there is no char array left to return. Then, I use the
same ft_isinset(2) approach as I did before, but now in a backwards going manner
and using a different iterator var 'j'. In the end I am left with indices 'i' 
and 'j' that inform me which section of 's1' should be kept. This data is fed
to ft_substr(3) which returns me the newly trimmed char array.
*/
