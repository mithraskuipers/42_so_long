/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:34:40 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/11/17 10:49:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strfiller(char *n_str, int ndigits, long n_long)
{
	n_str[ndigits] = '\0';
	ndigits--;
	if (n_long < 0)
	{
		n_str[0] = '-';
		n_long = n_long * -1;
	}
	if (n_long == 0)
	{
		n_str[0] = '0';
		return (n_str);
	}
	while (n_long > 0)
	{
		n_str[ndigits] = (n_long % 10) + '0';
		n_long = n_long / 10;
		ndigits--;
	}
	return (n_str);
}

char	*ft_itoa(int n)
{
	char	*n_str;
	int		ndigits;
	long	n_long;

	n_long = (long)n;
	ndigits = ft_ndigits(n_long);
	n_str = malloc(sizeof(char) * (ndigits + 1));
	if (!(n_str))
		return (NULL);
	return (ft_strfiller(n_str, ndigits, n_long));
}

/*
ft_ndigits(1) expects a long type integer and first checks whether the inputted
integer is negative or positive. If it is negative, it will increment our digit
counter to account for the minus sign. Next, it will iteratively count the 
number of digits in our integer by keeping track of how many times the integer
could be divided by 10. Finally, it returns the number of detected digits.

This implementation of ft_itoa(1) returns a char array 'n_str' that has been 
constructed from right to left. It only works with valid ints that do not start 
with 0. If the first the first digit of the int is a 0, it will fill in the 
'n_str' with zero and return the array. The user-specified int 'n' is typecasted
into a long int, of which the number of digits is extracted using ft_ndigits(1).
Now it calls ft_strfiller(3), which is a helper function for actually filling
our char array with the correct ascii values. It requires the empty array,
output from ft_ndigits(1), and the user-specified int (that is typecasted to 
long). First I check whether the int is negative, and if so, it writes a '-'
sign to the first index of the array and turn the int positive. Then, while 
'n_long' is greater than 0, determine the right-most digit using modulo 10, 
which is then written to the current index of the 's_str' after having been
converted to an ascii value. Then it updates 'n_long' by using int division 
(this drops the remainder) and 'decrement' the current index of the 'n_str'.
*/