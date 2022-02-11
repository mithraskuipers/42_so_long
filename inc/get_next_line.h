/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/04 13:41:04 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/11 18:35:21 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

char	*ft_strjoin_endline(char *s1, char *s2, int i, int j);
int		get_next_line(int fd, char **line);
void	*buf_move(char *src);
int		find_endnull(const char *s);

#endif