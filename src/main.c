#include "so_long.h"

int		ft_exit_failure(char *s)
{
	ft_putstr_fd("Error\n", 2); // Don't touch this. Subject wants this.
	ft_putstr_fd(s, 2);
	exit (EXIT_FAIL);
}

int		check_input_validity(int argc, char **argv)
{
	int	fd;
	if (argc < 2)
		ft_exit_failure("Please provide a map.");
	if (!(ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))) // werkt dit?
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

	fd = open(game->map.filepath, O_RDONLY);
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
		ft_exit_failure("Map is not rectangular.");
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
			else if ((!(game->map.map[i][j] != '0')) && (!(game->map.map[i][j] != '1')))
				(game->map.content.invalids)++;
		}
		i++;
	}
}

static void	read_map_into_memory(t_game *game)
{
	game->map.fd = open(game->map.filepath, O_RDONLY);
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
	game->map.fd = open(game->map.filepath, O_RDONLY);
	get_map_width(game);
	get_map_height(game);
	check_map_rectangular(game);
	game->px_x = game->map.ntiles_x * TILE_WIDTH;
	game->px_y = game->map.ntiles_y * TILE_WIDTH;
	read_map_into_memory(game);
	check_map_contents(game);
}


static void map_contents_init(t_game *game)
{
	game->map.content.players = 0;
	game->map.content.collectables = 0;
	game->map.content.exits = 0;
	game->map.content.invalids = 0;
}

int			main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	game->map.filepath = argv[1];
	map_contents_init(game);
	check_input_validity(argc, argv);
	parse_map(game);
	game->mlx.init = mlx_init();
	game->mlx.win = mlx_new_window(game->mlx.init, game->px_x, game->px_y, "TEST");
	mlx_loop(game->mlx.init);
	return (0);
}