/*
Als het gaat om de [][] coordinaten van een kaart hanteer je:
[row][col]

Als het gaat om de X and Y coordinaten (voor bijv. het printen van de tile),
dan werk je met X en Y logica. Hierbij X = col; Y = row.
col, row
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 13:13:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2022/02/21 13:13:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG

# define SO_LONG

#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"

#define EXIT_FAIL 1
#define TILE_WIDTH 64
#define N_IMAGES 19

#define W_KEY 13
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define ESC_KEY 53

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

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

static	int	ft_exit_failure(char *s);
static	int	close_win(t_game *game);
static	int	input(int key, t_game *game);
static void mover(t_game *game, int dirtile, int x, int y);
static void update_tiles(t_game *game, int x, int y, char c);
static void update_awareness(t_game *game, t_state *player);
static void draw_player(t_game *game);
static void draw_map(t_game *game);
static void cell_player(t_game *game, int row, int col, t_state *player);
static void	ft_map_failure(t_game *game, char *s);
static void	check_input_validity(int argc, char **argv);
static void get_dim(t_game *game, int fd, char *tmp, int ret);
static void cell_count_map_chars(t_game *game, int row, int col);
static void map_count_check(t_game *game);
static void	map_presence_borders(t_game *game, int i, int j);
static void	read_map_into_memory(t_game *game, int row);
static void	parse_map(int argc, char **argv, t_game *game);
static void xpm_init(t_game *game);
static void looper(t_game *game, int pic, int *height, int *width);
static void	load_xpm_sprites(t_game *game);
static void cell_looper(t_game *game, void (*f)());
static void cell_draw_walls(t_game *game, int row, int col);
static void cell_draw_collectable(t_game *game, int row, int col);
static void cell_player_pos(t_game *game, int row, int col);
static void cell_draw_door(t_game *game, int row, int col);
static void cell_draw_bg(t_game *game, int row, int col);
static void cell_draw_corners(t_game *game, int row, int col);

/* All valid input keys */
enum e_keycode
{
	KEY_UP = 13,
	KEY_DOWN = 1,
	KEY_LEFT = 0,
	KEY_RIGHT = 2,
	RESET = 15,
	ESC = 53
};

/* keycodes for keys that are independent of keyboard layout*/
enum
{
	KEY_RETURN = 0x24,
	KEY_TAB = 0x30,
	KEY_SPACE = 0x31,
	KEY_DELETE = 0x33,
	KEY_ESCAPE = 0x35,
	KEY_COMMAND = 0x37,
	KEY_SHIFT = 0x38,
	KEY_CAPSLOCK = 0x39,
	KEY_OPTION = 0x3A,
	KEY_CONTROL = 0x3B,
	KEY_RIGHTSHIFT = 0x3C,
	KEY_RIGHTOPTION = 0x3D,
	KEY_RIGHTCONTROL = 0x3E,
	KEY_FUNCTION = 0x3F,
	KEY_F17 = 0x40,
	KEY_VOLUMEUP = 0x48,
	KEY_VOLUMEDOWN = 0x49,
	KEY_MUTE = 0x4A,
	KEY_F18 = 0x4F,
	KEY_F19 = 0x50,
	KEY_F20 = 0x5A,
	KEY_F5 = 0x60,
	KEY_F6 = 0x61,
	KEY_F7 = 0x62,
	KEY_F3 = 0x63,
	KEY_F8 = 0x64,
	KEY_F9 = 0x65,
	KEY_F11 = 0x67,
	KEY_F13 = 0x69,
	KEY_F16 = 0x6A,
	KEY_F14 = 0x6B,
	KEY_F10 = 0x6D,
	KEY_F12 = 0x6F,
	KEY_F15 = 0x71,
	KEY_HELP = 0x72,
	KEY_HOME = 0x73,
	KEY_PAGEUP = 0x74,
	KEY_FORWARDDELETE = 0x75,
	KEY_F4 = 0x76,
	KEY_END = 0x77,
	KEY_F2 = 0x78,
	KEY_PAGEDOWN = 0x79,
	KEY_F1 = 0x7A,
	KEY_LEFTARROW = 0x7B,
	KEY_RIGHTARROW = 0x7C,
	KEY_DOWNARROW = 0x7D,
	KEY_UPARROW = 0x7E
};

#endif