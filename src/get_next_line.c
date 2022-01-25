/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 22:31:07 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/01/25 22:36:01 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buff_reader(char *buff_merged, int fd)
{
	int		nbytes;
	char	*buff_tmp;

	buff_tmp = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
	if (!(buff_tmp))
		return (NULL);
	while (!(ft_strchr(buff_merged, '\n')))
	{
		nbytes = read(fd, buff_tmp, BUFFER_SIZE);
		if (nbytes <= 0)
		{
			free (buff_tmp);
			if (nbytes == 0)
				return (buff_merged);
			return (NULL);
		}
		buff_tmp[nbytes] = '\0';
		buff_merged = ft_strjoin_gnl(buff_merged, buff_tmp, 0, 0);
	}
	free (buff_tmp);
	return (buff_merged);
}

static char	*obtain_line(char *buff_merged)
{
	char	*leftside;
	int		i;
	int		len;

	if (!buff_merged)
		return (NULL);
	len = ft_strlen_char(buff_merged, '\n');
	leftside = malloc(sizeof(char) * (len + 2));
	if (!leftside)
		return (NULL);
	i = 0;
	while (i < len)
	{
		leftside[i] = buff_merged[i];
		i++;
	}
	if (buff_merged[i] == '\n')
	{
		leftside[i] = buff_merged[i];
		i++;
	}
	leftside[i] = '\0';
	return (leftside);
}

static char	*buff_remainder(char *buff_merged)
{
	char	*remainder;
	int		start;
	int		i;

	start = ft_strlen_char(buff_merged, '\n');
	if (buff_merged[start] == '\0')
	{
		free(buff_merged);
		return (NULL);
	}
	remainder = malloc(((ft_strlen_char(buff_merged, '\0') - start) + 1));
	if (!remainder)
		return (NULL);
	start++;
	i = 0;
	while (buff_merged[start])
	{
		remainder[i] = buff_merged[start];
		start++;
		i++;
	}
	remainder[i] = '\0';
	free(buff_merged);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*buff_merged[OPEN_MAX];
	char		*left;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > OPEN_MAX))
		return (NULL);
	if (!ft_strchr(buff_merged[fd], '\n'))
		buff_merged[fd] = buff_reader(buff_merged[fd], fd);
	left = obtain_line(buff_merged[fd]);
	if (!left)
		return (NULL);
	if (buff_merged[fd][0] == '\0')
	{
		free(buff_merged[fd]);
		free(left);
		return (NULL);
	}
	buff_merged[fd] = buff_remainder(buff_merged[fd]);
	return (left);
}
