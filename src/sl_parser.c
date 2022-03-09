/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:02:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 15:28:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_dim(t_game *game, int fd, char *tmp, int ret)
{
	ret = get_next_line(fd, &tmp);
	if (ret > 0)
		game->map.ntiles_cols = ft_strlen(tmp);
	else if (ret == 0)
		exit_failure("Map is empty.");
	free (tmp);
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		if (ret == -1)
			break ;
		if ((ft_strlen(tmp)) != (size_t)game->map.ntiles_cols)
		{
			free(tmp);
			exit_failure("Map is not rectangle.");
		}
		game->map.ntiles_rows++;
		free (tmp);
	}
	game->map.ntiles_rows++;
	close(fd);
	if (ret < 0)
		exit_failure("File could not be read.");
}

static void	read_map_into_mem(t_game *game)
{
	int	ret;
	int	row;

	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		exit_failure("Failing to read the map.");
	}
	row = 0;
	game->map.map = malloc(sizeof(char *) * (game->map.ntiles_rows + 1));
	if (!(game->map.map))
		exit_failure("Malloc error.");
	while (row < game->map.ntiles_rows)
	{
		ret = get_next_line(game->map.fd, &game->map.map[row]);
		if (ret < 0)
			exit_failure("Failing to read the map.");
		row++;
	}
	close(game->map.fd);
}

void	parse_map(t_game *game)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		exit_failure("Error while reading the map. fd < 0");
	}
	get_dim(game, game->map.fd, 0, 0);
	game->px_row = game->map.ntiles_rows * TILE_WIDTH;
	game->px_col = game->map.ntiles_cols * TILE_WIDTH;
	read_map_into_mem(game);
	cell_check(game, check_char_validity);
	cell_check(game, count_chars);
	check_char_count(game);
	cell_check(game, check_borders);
}
