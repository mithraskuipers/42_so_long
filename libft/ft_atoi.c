/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/09 17:13:29 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 12:35:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(int c)
{
	if ((c == ' ') || (c == '\t') || (c == '\v') || (c == '\r') || (c == '\n') \
	|| (c == '\f'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	value;
	int	i;
	int	sign;

	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	value = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	return (value * sign);
}

/*
ft_atoi() starts by checking for correct input and begins by looping over the 
inputted char array. It only starts converting the array to int process when the
array reached non-whitespace chars. Then, if the first char is a '-' or '+', it
will process this information for determining the sign of the return value 
'nbr'. i.e. whether or not nbr should be negative or positive. Then, while the 
array consists of digits, it keeps 'growing' our 'nbr' such that the entire 
input array is converted into an integer. This process works from left to right,
by always first multiplying our nbr var by 10. The multiplication forces the nbr
to contain an additional digit, which can be used to 'add' the next number of 
the char array.
*/