/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_input.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:36:59 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 15:07:10 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parse_input(int key, t_game *game)
{
	if (key == KEY_UP)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_U].mlx_img;
		mover(game, game->map.player.u, 0, -1);
	}
	else if (key == KEY_DOWN)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_D].mlx_img;
		mover(game, game->map.player.d, 0, 1);
	}
	else if (key == KEY_LEFT)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_L].mlx_img;
		mover(game, game->map.player.l, -1, 0);
	}
	else if (key == KEY_RIGHT)
	{
		game->img[PLAYER].mlx_img = game->img[PLAYER_R].mlx_img;
		mover(game, game->map.player.r, 1, 0);
	}
	else if (key == ESC)
		stop_game(game);
	mlx_clear_window(game->mlx.instance, game->mlx.win);
	draw_map(game);
	return (0);
}
