/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sl_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 17:56:01 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/09 12:37:19 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_failure(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	exit (EXIT_FAILURE);
}

int	stop_game(t_game *game)
{
	mlx_destroy_window(game->mlx.instance, game->mlx.win);
	exit(EXIT_SUCCESS);
	return (1);
}

void	map_failure(t_game *game, char *s)
{
	int	i;

	i = 0;
	while ((i < game->map.ntiles_rows) && (game->map.map[i]))
	{
		free (game->map.map[i]);
		i++;
	}
	free (game->map.map);
	exit_failure(s);
}
