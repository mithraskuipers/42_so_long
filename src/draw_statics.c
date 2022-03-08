/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_statics.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:02:43 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 11:42:56 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cell_draw_walls(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if (row == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_U].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (row == (game->map.ntiles_rows - 1))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_D].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (col == 0)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_L].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if (col == (game->map.ntiles_cols - 1))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_R].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[STONE].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

void	cell_draw_door(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'E')
	{
		if (game->map.content.ncollectables != game->map.content.ncollected)
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[DOOR_C].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[DOOR_O].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

void	cell_draw_bg(t_game *game, int row, int col)
{
	mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
	game->img[BG].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
}

void	cell_draw_corners(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == '1')
	{
		if ((col == 0) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_UL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == 0) && (row == (game->map.ntiles_rows - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_LL].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols - 1)) && (row == 0))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_UR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
		else if ((col == (game->map.ntiles_cols - 1)) && \
		(row == (game->map.ntiles_rows - 1)))
			mlx_put_image_to_window(game->mlx.instance, game->mlx.win, \
			game->img[WALL_LR].mlx_img, (col * TILE_WIDTH), (row * TILE_WIDTH));
	}
}

void	draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			cell_player(game, row, col, &game->map.player);
			cell_draw_bg(game, row, col);
			cell_draw_collectable(game, row, col);
			cell_draw_door(game, row, col);
			cell_draw_walls(game, row, col);
			cell_draw_corners(game, row, col);
			cell_player_pos(game, row, col);
			col++;
		}
		row++;
	}
	draw_player(game);
}
