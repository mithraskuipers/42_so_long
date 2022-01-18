#include "so_long.h"
#include "../mlx/mlx.h"

#define EXIT_FAIL 1
#define IMG_WIDTH 64
#define IMG_HEIGHT 64

int		check_input(int argc, char **argv)
{
	int	fd;
	if (argc < 2)
	{
		ft_putstr_fd("Please provide a map. Exiting.", 1);
		exit(EXIT_FAIL);
		return (EXIT_FAIL); // todo error please input map
	}
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))) // werkt dit?
	{
		ft_putstr_fd("Please provide a map with .ber extension. Exiting.", 1);
		exit(EXIT_FAIL);
		return (EXIT_FAIL); // todo error not valid mapname
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Please provide a valid map. Exiting.", 1);
		exit(EXIT_FAIL);
		return (EXIT_FAIL); // todo error nothing read
	}
	return (0);
}

int		main(int argc, char **argv)
{

	check_input(argc, argv);




	return (0);
}