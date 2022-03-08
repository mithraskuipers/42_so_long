/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   xpm.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/08 12:47:51 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/08 13:17:36 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	store_xpm_paths(t_game *game)
{
	game->img[BG].path = "./assets/BG.xpm";
	game->img[WALL_L].path = "./assets/wall_l.xpm";
	game->img[WALL_R].path = "./assets/wall_r.xpm";
	game->img[WALL_U].path = "./assets/wall_u.xpm";
	game->img[WALL_D].path = "./assets/wall_d.xpm";
	game->img[PLAYER].path = "./assets/player_front.xpm";
	game->img[PLAYER_L].path = "./assets/player_left.xpm";
	game->img[PLAYER_R].path = "./assets/player_right.xpm";
	game->img[PLAYER_U].path = "./assets/player_back.xpm";
	game->img[PLAYER_D].path = "./assets/player_front.xpm";
	game->img[WALL_UL].path = "./assets/WALL_ul.xpm";
	game->img[WALL_UR].path = "./assets/WALL_ur.xpm";
	game->img[WALL_LL].path = "./assets/WALL_ll.xpm";
	game->img[WALL_LR].path = "./assets/WALL_lr.xpm";
	game->img[COLLECTABLE].path = "./assets/collectable.xpm";
	game->img[DOOR_C].path = "./assets/door_c.xpm";
	game->img[DOOR_O].path = "./assets/door_o.xpm";
	game->img[STONE].path = "./assets/stone.xpm";
}

void	load_xpm(t_game *game)
{
	int	i;

	i = 0;
	while (i < N_IMAGES)
	{
		game->img[i].mlx_img = mlx_xpm_file_to_image(game->mlx.instance, \
		game->img[i].path, &game->img[i].height, &game->img[i].width);
		i++;
	}
}
