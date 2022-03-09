/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 13:13:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/03/09 11:08:55 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG
#define SO_LONG

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

#define TILE_WIDTH 64
#define N_IMAGES 19

#define KEY_UP 13
#define KEY_DOWN 1
#define KEY_LEFT 0
#define KEY_RIGHT 2
#define RESET 15
#define ESC 53

#define BG 0
#define PLAYER 1
#define PLAYER_L 2
#define PLAYER_R 3
#define PLAYER_U 4
#define PLAYER_D 5
#define COLLECTABLE 6
#define EXIT 7
#define WALL_U 8
#define WALL_D 9
#define WALL_L 10
#define WALL_R 11
#define WALL_UL 12
#define WALL_UR 13
#define WALL_LL 14
#define WALL_LR 15
#define DOOR_C 16
#define DOOR_O 17
#define STONE 18

typedef struct s_mlx
{
	void		*instance;
	void		*win;
}				t_mlx;

typedef struct	s_content
{
	int	players;
	int	ncollectables;
	int	ncollected;
	int	exits;
	int	invalids;
	int	nsteps;
}				t_content;

typedef struct	s_state
{
	int	x;
	int	y;
	int u;
	int d;
	int l;
	int r;
	int dir;
}				t_state;

typedef struct	s_map
{
	t_content	content;
	char		*path;
	char		**map;
	int			fd;
	t_state		player;
	int			ntiles_cols;
	int			ntiles_rows;
}				t_map;

typedef struct	s_img
{
	char	*path;
	void	*mlx_img;

	int 	width;
	int		height;
}				t_img;

typedef	struct	s_game
{
	t_mlx		mlx;
	t_map		map;
	t_img		img[N_IMAGES];
	int			px_row;
	int			px_col;
	int			**walked_map;
}				t_game;

int		exit_failure(char *s);
int		stop_game(t_game *game);
int		parse_input(int key, t_game *game);
void	mover(t_game *game, int dirtile, int x, int y);
void	update_surrounding(t_game *game, t_state *player);
void	draw_player(t_game *game);
void	draw_map(t_game *game);
void	cell_player(t_game *game, int row, int col, t_state *player);
void	map_failure(t_game *game, char *s);
void	check_input_validity(int argc, char **argv);
void	count_chars(t_game *game, int row, int col);
void	check_char_count(t_game *game);
void	check_borders(t_game *game, int i, int j);
void	parse_map(t_game *game);
void	store_xpm_paths(t_game *game);
void	load_xpm(t_game *game);
void	cell_loop(t_game *game, void (*f)());
void	cell_draw_walls(t_game *game, int row, int col);
void	cell_draw_collectable(t_game *game, int row, int col);
void	cell_player_pos(t_game *game, int row, int col);
void	cell_draw_door(t_game *game, int row, int col);
void	cell_draw_bg(t_game *game, int row, int col);
void	cell_draw_corners(t_game *game, int row, int col);
void	update_tiles(t_game *game, int x, int y, char c);
void	check_char_validity(t_game *game, int row, int col);

#endif
