/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkuipers <mkuipers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 17:42:17 by mkuipers      #+#    #+#                 */
/*   Updated: 2021/11/17 22:56:11 by mkuipers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa(unsigned int n)
{
	char			*n_str;
	unsigned int	ndigits;

	if (n == 0)
		return (ft_strdup("0"));
	ndigits = ft_ndigits(n);
	n_str = ft_calloc(sizeof(char), (ndigits + 1));
	if (!(n_str))
		return (NULL);
	ndigits--;
	if (n == 0)
		return (n_str);
	while (n > 0)
	{
		n_str[ndigits] = (n % 10) + '0';
		n = n / 10;
		ndigits--;
	}
	return (n_str);
}
