#include "so_long.h"

/*
clear && make re && clear && ./so_long map1_5x5.ber
*/

static void	ft_exit_failure(char *s)
{
	ft_putstr_fd("Error\n", 2); // Don't touch this. Subject wants this.
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}

static void	ft_map_failure(t_game *game, char *s)
{
	int	i;

	i = 0;
	while (game->map.map[i])
	{
		free (game->map.map[i]);
		i++;
	}
	free (game->map.map);
	ft_exit_failure(s);
}

int		check_input_validity(int argc, char **argv)
{
	int	fd;
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1]))))
		ft_exit_failure("Please provide a map with .ber extension.");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_failure("Please provide a valid map.");
	}
	close(fd);
	return (0);
}

static void	get_map_width(t_game *game)
{
	char	buff[1];
	int		len;
	int		nbytes;

	buff[0] = '\0';
	nbytes = 1;
	len = 0;
	while (nbytes)
	{
		nbytes = read(game->map.fd, buff, 1);
		if (buff[0] != '\n')
			len++;
		else
			break ;
	}
	game->map.ntiles_x = len;
}

static void	get_map_height(t_game *game)
{
	int fd;
	int i;

	fd = open(game->map.path, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_exit_failure("File could not be opened.");
	}
	i = 1;
	while (get_next_line(game->map.fd))
		i++;
	game->map.ntiles_y = i;
	close(fd);
}

static void	check_map_rectangular(t_game *game)
{
	if (game->map.ntiles_x != game->map.ntiles_y)
		ft_map_failure(game, "Map is not rectangular.");
}

static void	check_map_contents(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.ntiles_y)
	{
		j = 0;
		while (j < game->map.ntiles_x)
		{
			j++;
			if (game->map.map[i][j] == 'P')
				(game->map.content.players)++;
			else if (game->map.map[i][j] == 'C')
				(game->map.content.collectables)++;
			else if (game->map.map[i][j] == 'E')
				(game->map.content.exits)++;
			else if ((!(game->map.map[i][j] != '0')) && \
			(!(game->map.map[i][j] != '1')))
				(game->map.content.invalids)++;
		}
		i++;
	}
}

static void	check_map_borders(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.ntiles_y)
	{
		j = 0;
		if ((i == 0) || (i == (game->map.ntiles_y) - 1))
		{
			while (j < game->map.ntiles_x)
			{
				if (game->map.map[i][j] != '1')
					ft_map_failure(game, "Your map is not enclosed in borders");
				j++;
			}
		}
		else
		{
			if ((game->map.map[i][0] != '1') || \
			(game->map.map[i][game->map.ntiles_x - 1] != '1'))
					ft_map_failure(game, "Your map is not enclosed in borders");
			j++;
		}
		i++;
	}
}

static void	read_map_into_memory(t_game *game)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	if (game->map.fd < 0)
	{
		close(game->map.fd);
		ft_exit_failure("Please provide a valid map.");
	}
	int i;

	i = 0;
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.ntiles_y + 1));
	if (!(game->map.map))
		ft_exit_failure("Malloc error.");
	while (i < game->map.ntiles_y)
	{
		game->map.map[i] = get_next_line(game->map.fd);
		i++;
	}
	close(game->map.fd);
}

static void	parse_map(t_game *game)
{
	game->map.fd = open(game->map.path, O_RDONLY);
	get_map_width(game);
	get_map_height(game);
	check_map_rectangular(game);
	game->px_x = game->map.ntiles_x * TILE_WIDTH;
	game->px_y = game->map.ntiles_y * TILE_WIDTH;
	read_map_into_memory(game);
	check_map_contents(game);
	check_map_borders(game);
}

static void map_contents_init(t_game *game)
{
	game->map.content.players = 0;
	game->map.content.collectables = 0;
	game->map.content.exits = 0;
	game->map.content.invalids = 0;
}

/*
static void	draw_map(t_game *game)
{
	int i = 32;
	int j = 32;

	int width;
	width = 32;

	game->img.path = "./assets/bg.xpm";
	game->img.mlx_img = mlx_xpm_file_to_image(game->mlx.init, game->img.path, &i, &j); //i en j zijn width en height
	//mlx_put_image_to_window(game->mlx.init, game->mlx.win, game->img.mlx_img, width, width); // pixel position

	int k = 0;
	int l = 0;
	while (k < game->map.ntiles_y)
	{
		l = 0;
		while (l < game->map.ntiles_x)
		{
			mlx_put_image_to_window(game->mlx.init, game->mlx.win, game->img.mlx_img, k * width, l * width);
			l++;
		}
		k++;
	}
}
*/

static void	draw_tile(t_game game, int i, int j, char *path)
{
	// xpm to image
	// image to window
}

static void	interpret_tile(t_game *game, int i, int j)
{
	if (game->map.map[i][j] == '1')
	{
		// TEKEN MUUR. NODIG: de coordinaten. heeft functie nodig die vraagt naar game (want mlx) + coordinaten + imagefile path
	}
}

static void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->map.ntiles_y)
	{
		j = 0;
		while (j < game->map.ntiles_x)
		{
			interpret_tile(game, i, j);
			j++;
		}
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	game->map.path = argv[1];
	map_contents_init(game);
	check_input_validity(argc, argv);
	parse_map(game);
	game->mlx.init = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.init, game->px_x, game->px_y, "MITHRAS");
	
	draw_map(game);
	
	
	mlx_loop(game->mlx.init);
	return (0);
}