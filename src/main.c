#include "so_long.h"
#include "../mlx/mlx.h"

/*
int		ft_exit_failure(char *s)
{
	ft_putstr_fd("Error.\n", 2);
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}

int		check_input(int argc, char **argv)
{
	int	fd;
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))) // werkt dit?
		ft_exit_failure("Please provide a map with .ber extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_exit_failure("Please provide a valid map.");
	return (0);
}

int	open_file(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		ft_exit_failure("Failed to open the map.");
	return (fd);
}

int		map_width(int fd)
{
	char	buff[1];
	int		len;
	int		nbytes;

	buff[0] = '\0';
	nbytes = 1;
	len = 0;
	while (nbytes)
	{
		nbytes = read(fd, buff, 1);
		if (buff[0] != '\n')
			len++;
		else
			break ;
	}
	return (len);
}

int		map_height(int fd, int map_width)
{
	char	buff[1];
	int		count;
	int		nbytes;
	int		i;

	count = 1;
	nbytes = 1;
	i = 0;
	buff[0] = '\0';

	while (nbytes)
	{
		nbytes = read(fd, buff, 1);
		if (i == ((map_width * TILE_WIDTH) / TILE_WIDTH))
		{
			count++;
			i = 0;
		}
		else
			i++;
	}
	return (count);
}

void	read_texture_paths(t_game *game)
{
	game->img[0].path = "./assets/env0.xpm";
	game->img[1].path = "./assets/env1.xpm";
	game->img[2].path = "./assets/env2.xpm";
}

void	get_map_dim(t_game *game, char *filepath)
{
	int	fd;

	fd = open_file(filepath);
	game->map.filepath = filepath;
	game->map.width = map_width(fd);
	game->map.height = map_height(fd, game->map.width);
	game->win_px_x = game->map.width * TILE_WIDTH;
	game->win_px_y = game->map.height * TILE_WIDTH;
}


static void	check_input_validity(t_game *game)
{

}

static void	check_map_validity(t_game *game)
{

}

static void	parser(char **argv, t_game *game)
{
	//check_input(argc, argv);
	check_input_validity(game);
	parse_map_validity(game);
}
*/

static void init(t_game *game)
{
	game->map.n_xtiles = 0;
	game->map.n_ytiles = 0;
}

int			main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	init(game);
	//parser(argv, game);

	/*
	get_map_dim(game, argv[1]);
	game->mlx.init = mlx_init();
	if (!(game->mlx.init))
		ft_exit_failure("MLX initialization failed.");
	read_texture_paths(game);
	create_images(game);
	game->mlx.win = mlx_new_window(game->mlx.init, game->win_px_x, game->win_px_y, "so_long window");
	if (!(game->mlx.win))
		return (ft_exit_failure("MLX window creation fail."));
	draw_bg(game);
	mlx_loop(game->mlx.init);
	*/
	return (0);
}