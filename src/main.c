#include "so_long.h"




#define EXIT_FAIL 1
#define IMG_WIDTH 32
#define IMG_HEIGHT 32







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
	data->win_px_y = (ft_countlines_fd(fd) * IMG_HEIGHT);

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
	//printf("%d", data.win_px_y);
	//printf("%d", data.size_x);
	return (0);
}

// waar komt EXIT_FAILURE vandaan?