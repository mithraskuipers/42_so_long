#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"
#include "../mlx/mlx.h"

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

} 				t_img;

typedef struct	s_map
{
	char	*filepath;
	int		n_xtiles;
	int		n_ytiles;

}				t_map;

typedef	struct	s_game
{
	t_mlx	mlx;
	t_map	map;
	t_img	img[N_IMAGES];
	int		px_x;
	int		px_y;
}				t_game;