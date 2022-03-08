/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 14:20:34 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 13:45:45 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2, int i, int j)
{
	char	*str;

	if ((!(s1)) || (!(s2)))
		return (NULL);
	str = malloc(sizeof(char) * (pos_nl(s1) + pos_nl(s2) + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	str[i + j] = '\0';
	return (str);
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

static int	buff_merge(char *buf, char **line, int ret, int fd)
{
	if (buf[0] == '\0')
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
		{
			free(*line);
			return (-1);
		}
		else if (ret == 0)
			return (0);
		buf[ret] = '\0';
	}
	*line = gnl_strjoin(*line, buf, 0, 0);
	if (!*line)
		return (-1);
	if (buf[pos_nl(buf)] == '\n')
	{
		buff_mover(buf);
		return (1);
	}
	buf[0] = '\0';
	return (buff_merge(buf, line, ret, fd));
}

int	get_next_line(int fd, char **line)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;

	if ((!line) || (fd < 0) || (BUFFER_SIZE <= 0) || (read(fd, 0, 0) < 0))
		return (-1);
	*line = malloc(sizeof(char));
	if (!*line)
		return (-1);
	*line[0] = '\0';
	ret = 0;
	ret = buff_merge(buf[fd], line, ret, fd);
	if (ret == -1)
		*line = NULL;
	return (ret);
}
