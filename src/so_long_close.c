/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_close.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 17:56:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/21 18:02:13 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit_failure(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}

 int close_win(t_game *game)
{
	mlx_destroy_window(game->mlx.instance, game->mlx.win);
	exit(EXIT_SUCCESS);
	return (1);
}