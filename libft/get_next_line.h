/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 14:20:38 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/09 22:43:26 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int		get_next_line(int fd, char **dp);
int		pos_nl(const char *s);
void	*buff_mover(char *src);
char	*gnl_strjoin(char *s1, char *s2, int i, int j);

#endif