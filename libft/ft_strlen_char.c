/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen_char.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 18:11:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/01/18 21:28:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_char(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	if (c == '\0')
	{
		while (s[i])
			i++;
		return (i);
	}
	else
	{
		while (s[i] && s[i] != c)
		{
			i++;
		}
		return (i);
	}
}