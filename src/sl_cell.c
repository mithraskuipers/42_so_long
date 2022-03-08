/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cell.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 12:59:17 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 11:39:54 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	cell_looper(t_game *game, void (*f)())
{
	int	row;
	int	col;

	row = 0;
	while (row < game->map.ntiles_rows)
	{
		col = 0;
		while (col < game->map.ntiles_cols)
		{
			f(game, row, col);
			col++;
		}
		row++;
	}
}

void	cell_player_pos(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
	{
		game->map.player.y = row;
		game->map.player.x = col;
	}
}

void	count_chars(t_game *game, int row, int col)
{
	if (game->map.map[row][col] == 'P')
		(game->map.content.players)++;
	else if (game->map.map[row][col] == 'C')
		(game->map.content.ncollectables)++;
	else if (game->map.map[row][col] == 'E')
		(game->map.content.exits)++;
	else if ((!(game->map.map[row][col] != '0')) && \
	(!(game->map.map[row][col] != '1')))
		(game->map.content.invalids)++;
}

void	cell_player(t_game *game, int row, int col, t_state *player)
{
	if (game->map.map[row][col] == 'P')
	{
		player->x = col;
		player->y = row;
		player->u = game->map.map[player->y - 1][player->x];
		player->d = game->map.map[player->y + 1][player->x];
		player->l = game->map.map[player->y][player->x - 1];
		player->r = game->map.map[player->y][player->x + 1];
	}
}
