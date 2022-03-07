/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 14:02:24 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/07 14:03:19 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	parse_map(int argc, char **argv, t_game *game)
{
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (ft_strrchr(argv[1], '.') == 0 || ft_strncmp(ft_strrchr(argv[1], '.'), \
	".ber", 5))
		ft_exit_failure("Please provide a map with .ber extension.");
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Error while reading the map. fd < 0");
	}
	get_dim(game, game->map.fd, 0, 0);
	game->px_row = game->map.ntiles_rows * TILE_WIDTH;
	game->px_col = game->map.ntiles_cols * TILE_WIDTH;
	read_map_into_memory(game, 0);
}

void	read_map_into_memory(t_game *game, int row)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Failing to read the map.");
	}
	row = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_rows+1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (row < game->map.ntiles_rows)
	{
		int ret = get_next_line(game->map.fd, &game->map.map[row]);
		if (ret < 0)
			ft_exit_failure("Failing to read the map.");
		row++;
	}
	close(game->map.fd);
}

void get_dim(t_game *game, int fd, char *tmp, int ret)
{
	ret = get_next_line(fd, &tmp);
	if (ret > 0)
		game->map.ntiles_cols = ft_strlen(tmp);
	else if (ret == 0)
		ft_exit_failure("Map is empty.");
	while (ret)
	{
		ret = get_next_line(fd, &tmp);
		if (ret == -1)
			break;
		if ((ft_strlen(tmp)) != (size_t)game->map.ntiles_cols)
		{
			free(tmp);
			ft_exit_failure("Map is not Rectangle.");
		}
		game->map.ntiles_rows++;
	}
	game->map.ntiles_rows++;
	close(fd);
	if (ret < 0)
		ft_exit_failure("File could not be read.");
}