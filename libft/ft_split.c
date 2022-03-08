/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:36:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:36:25 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countparts(const char *s, char c)
{
	size_t	i;
	int		nparts;

	i = 0;
	nparts = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			nparts++;
			while (s[i] && s[i] != c)
				i++;
		}
		else if (s[i] && s[i] == c)
			i++;
	}
	return (nparts);
}

static char	**dp_clean(char **dp, size_t dp_i)
{
	while (dp_i > 0)
	{
		dp_i--;
		free(dp[dp_i]);
	}
	free(dp);
	return (NULL);
}

static char	**ft_split_helper(char **dp, const char *s, char c)
{
	size_t	s_i;
	size_t	dp_i;
	size_t	wordstart;

	s_i = 0;
	dp_i = 0;
	while (s_i < ft_strlen(s))
	{
		if ((s[s_i] != c) && (s_i < ft_strlen(s)))
		{
			wordstart = s_i;
			while ((s[s_i] != c) && (s_i < ft_strlen(s)))
				s_i++;
			dp[dp_i] = ft_substr(s, wordstart, (s_i - wordstart));
			if (!dp[dp_i])
				return (dp_clean(dp, dp_i));
			dp_i++;
		}
		s_i++;
	}
	return (dp);
}

char	**ft_split(char const *s, char c)
{
	char	**dp;

	if (!(s))
		return (NULL);
	dp = ft_calloc((ft_countparts(s, c) + 1), sizeof(char *));
	if (!(dp))
		return (NULL);
	return (ft_split_helper(dp, s, c));
}

/*
ft_countparts(2) computes the number of sections in the char array 's', whenever
the array is split into section using the char 'c' as separator value. Starting
at the beginning of the array, it checks whether the current char is NOT equal
to the user-specified separator value, indicating the START of a new section. 
It then increments the 'nparts' var, which is my count var for the number of
sections detected. Then, it will loop over this newly found section until it has
reached a value that is equal to the separator value, indicating the END of the
found section.

ft_split(2) expects a character array 's' and separator variable 'c'. Then using 
ft_countparts(2), it determines the number of parts that the character array
can be divided into when it separates the parts using the user specific 
separator var 'c'. The outcome is used to determine how much memory needs to be
allocated for the necessary double pointer. Then we iterate over each of the
chars of 's', and as long as we have not reached the end, we check for each
char if it is NOT equal to the separator variable. If that is the case, we know
we have found the start of a new word. This start index is saved separately in
'wordstart', and then we iterate over 's' until we have reached the separator
variable, informing me that we have reached the end of the current word. We then
have enough information to use ft_substr(3) to extract the relevant part of 's'
and store that in the correct position of our double pointer. We end our double
pointer with a null terminator and return the double pointer.
*/