/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 18:33:47 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/11 19:30:08 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
char	*ft_strjoin_endline(char *s1, char *s2, int i, int j)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (find_endnull(s1) + find_endnull(s2) + 1));
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

int		find_endnull(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	return (i);
}

void	*buf_move(char *src)
{
	size_t i;
	size_t j;

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
static int		createline(char *buf, char **line, int ret, int fd)
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
	*line = ft_strjoin_endline(*line, buf, 0, 0);
	if (!*line)
		return (-1);
	if (buf[find_endnull(buf)] == '\n')
	{
		buf_move(buf);
		return (1);
	}
	buf[0] = '\0';
	return (createline(buf, line, ret, fd));
}

int				get_next_line(int fd, char **line)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	int			ret;

	if (!line || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
		return (-1);
	*line = malloc(sizeof(char));
	if (!*line)
		return (-1);
	*line[0] = '\0';
	ret = 0;
	ret = createline(buf[fd], line, ret, fd);
	if (ret == -1)
		*line = NULL;
	return (ret);
}