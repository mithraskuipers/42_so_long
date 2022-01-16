#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"

typedef	struct	s_data
{
	void	*mlx;
	void	*win;
	int		win_px_x;
	int		win_px_y;
	int		stepcount;
	int		collcount;
}				t_data;