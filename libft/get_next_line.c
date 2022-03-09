/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 14:20:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/09 22:43:04 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2, int i, int j)
{
	char	*s_new;

	if ((!(s1)) || (!(s2)))
		return (NULL);
	s_new = malloc(sizeof(char) * (pos_nl(s1) + pos_nl(s2) + 1));
	if (!s_new)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		s_new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		s_new[i + j] = s2[j];
		j++;
	}
	free(s1);
	s_new[i + j] = '\0';
	return (s_new);
}

int	pos_nl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

void	*buff_mover(char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != '\n')
		j++;
	j++;
	while (src[j - 1] != '\0')
	{
		src[i] = src[j];
		i++;
		j++;
	}
	return (src);
}

static int	buff_merge(char *buff, char **dp, int ret, int fd)
{
	if (buff[0] == '\0')
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
		{
			free(*dp);
			return (-1);
		}
		else if (ret == 0)
			return (0);
		buff[ret] = '\0';
	}
	*dp = gnl_strjoin(*dp, buff, 0, 0);
	if (!(*dp))
		return (-1);
	if (buff[pos_nl(buff)] == '\n')
	{
		buff_mover(buff);
		return (1);
	}
	buff[0] = '\0';
	return (buff_merge(buff, dp, ret, fd));
}

int	get_next_line(int fd, char **dp)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;

	if ((!dp) || (fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, 0, 0) < 0))
		return (-1);
	*dp = malloc(sizeof(char));
	if (!*dp)
		return (-1);
	*dp[0] = '\0';
	ret = 0;
	ret = buff_merge(buff[fd], dp, ret, fd);
	if (ret == -1)
		*dp = NULL;
	return (ret);
}
