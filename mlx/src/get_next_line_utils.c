/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/04 13:41:14 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/01/25 22:35:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*s_uc;

	i = 0;
	s_uc = (char *)s;
	if (!s)
		return (NULL);
	while (s_uc[i])
	{
		if (s_uc[i] == (char)c)
			return (&s_uc[i]);
		i++;
	}
	if (s_uc[i] == (char)c)
		return (&s_uc[i]);
	return (NULL);
}

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

char	*ft_strjoin_gnl(char *s1, char *s2, int i, int j)
{
	char	*s_new;

	if (!s2)
		return (s1);
	s_new = malloc((ft_strlen_char(s1, '\0') + ft_strlen_char(s2, '\0')) + 1);
	if (!s_new)
		return (NULL);
	while (s1 && s1[i])
	{
		s_new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s_new[i + j] = s2[j];
		j++;
	}
	s_new[i + j] = '\0';
	free(s1);
	return (s_new);
}
