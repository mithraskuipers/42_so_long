#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"
#include "../mlx/mlx.h"
//#include <mlx.h>

typedef struct	s_img
{
	void	*bg;
} 				t_img;

typedef	struct	s_game
{
	void	*mlx;
	void	*win;
	int		win_px_x;
	int		win_px_y;
	int		stepcount;
	int		collcount;
	t_img	img;
}				t_game;

