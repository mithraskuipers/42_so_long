#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"
#include "../mlx/mlx.h"
#include "get_next_line.h"

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
#define FOOT 18

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

/* Prototypes */
/* generic */
static	void	ft_exit_failure(char *s);
static	void	ft_map_failure(t_game *game, char *s);
static	void	check_input_validity(int argc, char **argv);
static	void	get_map_width(t_game *game);
static	void	get_map_height(t_game *game);
//static	void	check_map_rectangular(t_game *game);
static	void	map_count_check(t_game *game);
static	void	map_presence_borders(t_game *game, int i, int j);
static	void	read_map_into_memory(t_game *game, char *s, int row);
//static	void	parse_map(t_game *game);
static void		parse_map(int argc, char **argv, t_game *game);
static	void	xpm_init(t_game *game);
static	void	load_xpm_sprites(t_game *game);

/* cell functions */

static	void	cell_looper(t_game *game, void (*f)());
static	void	draw_map(t_game *game);

static	void	cell_draw_bg(t_game *game, int row, int col);
static	void	cell_draw_corners(t_game *game, int row, int col);
static	void	cell_draw_obstacles(t_game *game, int row, int col);
static	void 	cell_draw_door(t_game *game, int row, int col);
static	void	cell_draw_player(t_game *game, int x, int y);
static	void	cell_player(t_game *game, int row, int col, t_state *player);
static	void	cell_player_pos(t_game *game, int row, int col);
static	void	cell_count_map_chars(t_game *game, int row, int col);

/* standalone */
static void draw_player(t_game *game);
static void update_awareness(t_game *game, t_state *player);
static void update_tiles(t_game *game, int x, int y, char c);

/* printer functions */
static	void	print_player_cross(t_game *game);
//static	void	print_player_pos(t_game *game);
//static	void	print_player_state(t_game *game);
static	void	print_map(t_game *game);

/* controller */
int				input(int key, t_game *game);
static void		mover(t_game *game, int dirtile, int x, int y);
static void print_status(char *s, int n);

static void cell_draw_collectable(t_game *game, int row, int col);
static void get_dim(t_game *game, int fd, char *tmp, int ret);

/*
clear && make re && clear && ./so_long map1_5x5.ber
*/

/*
Als het gaat om de [][] coordinaten van een kaart hanteer je:
[row][col]

Als het gaat om de X and Y coordinaten (voor bijv. het printen van de tile),
dan werk je met X en Y logica. Hierbij X = col; Y = row.
col, row
*/





// COUNT COLLECTED APPLES
// IF THAT MATCHES THE COUNTED APPLES AT INIT, UPDATE DOOR




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


#ifndef KEYS_H
# define KEYS_H

enum
{
	KEY_A = 0x00,
	KEY_S = 0x01,
	KEY_D = 0x02,
	KEY_F = 0x03,
	KEY_H = 0x04,
	KEY_G = 0x05,
	KEY_Z = 0x06,
	KEY_X = 0x07,
	KEY_C = 0x08,
	KEY_V = 0x09,
	KEY_B = 0x0B,
	KEY_Q = 0x0C,
	KEY_W = 0x0D,
	KEY_E = 0x0E,
	KEY_R = 0x0F,
	KEY_Y = 0x10,
	KEY_T = 0x11,
	KEY_1 = 0x12,
	KEY_2 = 0x13,
	KEY_3 = 0x14,
	KEY_4 = 0x15,
	KEY_6 = 0x16,
	KEY_5 = 0x17,
	KEY_EQUAL = 0x18,
	KEY_9 = 0x19,
	KEY_7 = 0x1A,
	KEY_MINUS = 0x1B,
	KEY_8 = 0x1C,
	KEY_0 = 0x1D,
	KEY_RIGHTBRACKET = 0x1E,
	KEY_O = 0x1F,
	KEY_U = 0x20,
	KEY_LEFTBRACKET = 0x21,
	KEY_I = 0x22,
	KEY_P = 0x23,
	KEY_L = 0x25,
	KEY_J = 0x26,
	KEY_QUOTE = 0x27,
	KEY_K = 0x28,
	KEY_SEMICOLON = 0x29,
	KEY_BACKSLASH = 0x2A,
	KEY_COMMA = 0x2B,
	KEY_SLASH = 0x2C,
	KEY_N = 0x2D,
	KEY_M = 0x2E,
	KEY_PERIOD = 0x2F,
	KEY_GRAVE = 0x32,
	KEY_KEYPADDECIMAL = 0x41,
	KEY_KEYPADMULTIPLY = 0x43,
	KEY_KEYPADPLUS = 0x45,
	KEY_KEYPADCLEAR = 0x47,
	KEY_KEYPADDIVIDE = 0x4B,
	KEY_KEYPADENTER = 0x4C,
	KEY_KEYPADMINUS = 0x4E,
	KEY_KEYPADEQUALS = 0x51,
	KEY_KEYPAD0 = 0x52,
	KEY_KEYPAD1 = 0x53,
	KEY_KEYPAD2 = 0x54,
	KEY_KEYPAD3 = 0x55,
	KEY_KEYPAD4 = 0x56,
	KEY_KEYPAD5 = 0x57,
	KEY_KEYPAD6 = 0x58,
	KEY_KEYPAD7 = 0x59,
	KEY_KEYPAD8 = 0x5B,
	KEY_KEYPAD9 = 0x5C
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