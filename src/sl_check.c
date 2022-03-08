/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 14:35:57 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 15:12:39 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_input_validity(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))))
		exit_failure("Please provide a map with .ber extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_failure("Error while reading the map. fd < 0");
	}
	close(fd);
}

void	map_count_elements(t_game *game)
{
	if (game->map.content.players > 1)
		exit_failure("Your map has more than 1 player spawnpoint.");
	else if (game->map.content.players < 1)
		exit_failure("Your map does not have 1 player spawnpoint.");
	if (game->map.content.exits > 1)
		exit_failure("Your map has more than 1 exit.");
	else if (game->map.content.exits < 1)
		exit_failure("Your map does not have 1 exit.");
}

void	map_presence_borders(t_game *game, int i, int j)
{
	if ((i == 0) || (i == (game->map.ntiles_rows) - 1))
	{
		if (game->map.map[i][j] != '1')
			map_failure(game, "Your map is not enclosed in borders");
	}
	if ((j == 0) || (j == (game->map.ntiles_cols) - 1))
	{
		if (game->map.map[i][j] != '1')
			map_failure(game, "Your map is not enclosed in borders");
	}
}
