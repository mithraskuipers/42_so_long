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

void	map_parser(t_map *map)
{

	int	fd;
	int	i;
	i = 0;
	map->n_rows = ft_nlines_fd(???);


}


int		main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
	{
		exit (EXIT_FAIL);
		return (EXIT_FAIL);
	}
	check_input(argc, argv);
	parse_map(&map);



	return (0);
}