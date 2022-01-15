#include <stdio.h>
#include <fcntl.h>
#include "../libftplusplus/libft.h"

typedef	struct	s_data
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	int		stepcount;
	int		collcount;
}				t_data;