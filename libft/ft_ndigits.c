/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ndigits.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 10:49:11 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/11/17 11:55:22 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ndigits(long n)
{
	int	ndigits;

	ndigits = 0;
	if (n < 0)
	{
		ndigits++;
		n = n * -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		ndigits++;
	}
	return (ndigits);
}
