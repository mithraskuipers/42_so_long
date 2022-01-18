#include "so_long.h"
#include "../mlx/mlx.h"

#define EXIT_FAIL 1
#define IMG_WIDTH 64
#define IMG_HEIGHT 64

void	ft_exit_failure(char *s)
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

/*
int	ft_nlines_fd(char *filepath)
{
	int	nlines;
	int	fd;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_exit_failure("Please provide a valid map.");
		return (EXIT_FAIL);
	}
	nlines = 0;
}
*/


//map_width = 

/*
{
	//map->width = ft_strlen_char(filepath, '\n');
	//map->width = ft_strlen_char(filepath, '\n'); // this is not good. you want not the file path, but contents of the file
	
	//while (file[root->game->width] && file[root->game->width] != '\n')
	//	root->game->width++;
	//if (root->game->width == 0 || file[root->game->width] == 0)
	//{
	//	free(file);
	//	root_destroy(root, "map file is invalid", 0);
	//}

}
*/

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




void	map_parser(t_map *map, char *filepath)
{

	int	fd;
	
	fd = open_file(filepath);
	
	//int	i;
	//i = 0;
	//map->n_rows = ft_nlines_fd(&filepath);
	map->filepath = filepath;
	//ft_putstr_fd(filepath, 1);
	map->width = map_width(fd);
	map->height = map_height(fd);
	ft_putstr_fd(ft_itoa(map->width), 1);
}


int		main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	game = malloc(sizeof(t_game));
	map = malloc(sizeof(t_map));
	if (!(game))
		ft_exit_failure("Memory allocation issue.");
	check_input(argc, argv);
	map_parser(map, argv[1]);
	//printf("%d", map->width);
	//printf("%s", ft_strchr(argv[1], 1));



	return (0);
}