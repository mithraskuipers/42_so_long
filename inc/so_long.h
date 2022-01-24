#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"
#include "../mlx/mlx.h"
//#include <mlx.h>

#define EXIT_FAIL 1
#define TILE_WIDTH 32
#define N_IMAGES 3

typedef struct s_mlx
{
	void	*init;
	void	*win;
}				t_mlx;




typedef struct	s_img
{
	void	*img;
	char	*path;
	int		x;
	int		y;
	int		is_valid;
	int		bpp;
	int		line_size;
	int		endian;
	char	*pixels;
} 				t_img;

typedef struct	s_map
{
	char	*filepath;
	int		width;
	int		height;
}				t_map;

typedef	struct	s_game
{
	t_mlx	mlx;
	t_map	map;
	t_img	img[N_IMAGES];
	int		win_px_x;
	int		win_px_y;
}				t_game;