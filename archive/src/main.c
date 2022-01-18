#include "so_long.h"
#include "../mlx/mlx.h"

#define EXIT_FAIL 1
#define IMG_WIDTH 64
#define IMG_HEIGHT 64


void	exit_error(void)
{
	printf("Error\nwrong map dimensions\n");
	exit(EXIT_FAILURE);
}

int	ft_count_lines(int fd, int x, int img_w)
/* returns how many lines the file of fd contains */
{
	char	buffer[1];
	int		linecount;
	int		bytes;
	int		i;

	i = 0;
	buffer[0] = '\0';
	linecount = 1;
	bytes = 1;
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (bytes != 1 && i != (x / img_w))
			exit_error();
		if (i == (x / img_w))
		{
			linecount++;
			i = 0;
		}
		else
			i++;
	}
	return (linecount);
}




void	ft_windim(t_data *data, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("nothing read from map");
		exit(EXIT_FAIL);
	}
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))))
	{
		printf("mapname not correct");
		exit(EXIT_FAIL);
	}
	data->win_px_x = (ft_strlen_fd(fd) * IMG_WIDTH);
	//data->win_px_y = (ft_countlines_fd(fd) * IMG_HEIGHT);
	//data->win_px_y = (ft_countlines_fd(fd) * IMG_HEIGHT);
	data->win_px_y = (ft_count_lines(fd, data->win_px_x, IMG_WIDTH) * IMG_HEIGHT);
}

void	ft_render_bg(t_data *data)
{
	int	line;
	int	x;

	line = 0;
	while (line < (data->win_px_y))
	{
		x = 0;
		while (x < (data-> win_px_x))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img.bg, x, line);
			x = x + IMG_WIDTH;
		}
		line = line + IMG_HEIGHT;
	}
}







int	main(int argc, char **argv)
{
	t_data	data;
	if (argc < 2)
	{
		printf("MAIN->EXITING\n");
		exit(EXIT_FAIL);
	}
	printf("MAIN->PROCEEDING\n");
	ft_windim(&data, argv);
	//printf("x width %d\n", data.win_px_x);
	//printf("y height %d\n", data.win_px_y);

	char	*relative_path;
	int		img_width;
	int		img_height;

	//return (0);
	//return(0);
	data.mlx = mlx_init();

	relative_path = "./assets/bg.xpm";
	//return (0);
	data.img.bg = mlx_xpm_file_to_image(data.mlx, relative_path, &img_width, &img_height);

	//relative_path = "./assets/bg.png";
	//return (0);
	//data.img.bg = mlx_png_file_to_image(data.mlx, relative_path, &img_width, &img_height);

	data.win = mlx_new_window(data.mlx, data.win_px_x, data.win_px_y, "./so_long"); // pointer mlx init, x dim, y dim, exec.
	ft_render_bg(&data);
	//ft_render_frame(&data);
	mlx_loop(data.mlx);
	return (0);
	*/
}

// waar komt EXIT_FAILURE vandaan?