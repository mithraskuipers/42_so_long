/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_draw.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 15:15:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/10 14:22:53 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			//cell_player_pos(game, row, col);
			col++;
		}
		row++;
	}
	draw_player(game);
}
