#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"
#include "../mlx/mlx.h"
#include "get_next_line.h"


#define EXIT_FAIL 1
#define TILE_WIDTH 64
#define N_IMAGES 12

#define BG 0
#define PLAYER 1
#define COLLECTIBLE 2
#define EXIT 3
#define WALL_U 4
#define WALL_D 5
#define WALL_L 6
#define WALL_R 7
#define CORNER_UL 8
#define CORNER_UR 9
#define CORNER_LL 10
#define CORNER_LR 11

typedef struct s_mlx
{
	void		*init;
	void		*win;
}				t_mlx;

typedef struct	s_content
{
	int			players;
	int			collectables;
	int			exits;
	int			invalids;
}				t_content;

typedef struct	s_map
{
	t_content	content;
	char		*path;
	char		**map;
	int			fd;
	int			ntiles_x;
	int			ntiles_y;
}				t_map;

typedef struct	s_img
{
	char	*path;
	void	*mlx_img;
}				t_img;

typedef	struct	s_game
{
	t_mlx		mlx;
	t_map		map;
	t_img		img[N_IMAGES];
	int			px_x;
	int			px_y;
}				t_game;