/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 17:56:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/07 13:07:00 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit_failure(char *s)
{
	perror(s);
	exit (EXIT_FAIL);
}

 int close_win(t_game *game)
{
	mlx_destroy_window(game->mlx.instance, game->mlx.win);
	exit(EXIT_SUCCESS);
	return (1);
}
