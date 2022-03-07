/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_dynamics.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:37:50 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/07 13:31:51 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void mover(t_game *game, int dirtile, int x, int y)
{
	if ((dirtile != '0') && (dirtile != 'C') && (dirtile != 'E'))
		return ;
	if (dirtile == 'E')
	{
		if (game->map.content.ncollected == game->map.content.ncollectables)
			exit(1);
		else
			return ;
	}
	game->map.content.nsteps++;
	ft_printf("You moved %d times.\n", game->map.content.nsteps);
	update_tiles(game, game->map.player.x, game->map.player.y, '0');
	update_tiles(game, (game->map.player.x + x), (game->map.player.y + y), 'P');
	game->map.player.y = game->map.player.y + y;
	game->map.player.x = game->map.player.x + x;
	update_awareness(game, &game->map.player);
}

void update_tiles(t_game *game, int x, int y, char c)
{
	if (game->map.map[y][x] == 'C')
		game->map.content.ncollected++;
	game->map.map[y][x] = c;
}

void update_awareness(t_game *game, t_state *player)
{
	player->u = game->map.map[player->y-1][player->x];
	player->d = game->map.map[player->y+1][player->x];
	player->l = game->map.map[player->y][player->x-1];
	player->r = game->map.map[player->y][player->x+1];
}

void draw_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
	game->img[PLAYER].mlx_img, (game->map.player.x * TILE_WIDTH), \
	(game->map.player.y * TILE_WIDTH));
}

void cell_draw_collectable(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'C')
	{
		row = (row * TILE_WIDTH);
		col = (col * TILE_WIDTH);
		mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
		game->img[COLLECTABLE].mlx_img, col, row);
	}
}