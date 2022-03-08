/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 17:43:43 by mkuipers      #+#    #+#                 */
/*   Updated: 2021/11/19 13:43:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_utoa_base(unsigned long long n, int base)
{
	long long	ndigits;
	char		*s;
	char		*base_set;

	if (n == 0)
		return (ft_strdup("0"));
	ndigits = ft_undigits_base((unsigned long long)n, base);
	s = ft_calloc((ndigits + 1), sizeof(char));
	base_set = ft_strdup("0123456789abcdef");
	if ((!(base_set)) || (!(s)))
		return (NULL);
	s[ndigits] = 0;
	while ((ndigits) && (n))
	{
		ndigits--;
		s[ndigits] = base_set[n % base];
		n = n / base;
	}
	free (base_set);
	return (s);
}
