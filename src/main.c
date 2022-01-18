#include "so_long.h"
#include "../mlx/mlx.h"

#define EXIT_FAIL 1
#define IMG_WIDTH 64
#define IMG_HEIGHT 64
#define TILE_WIDTH 32

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

/*
int	ft_count_lines(int fd, int x, int img_w)
//returns how many lines the file of fd contains
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
*/


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
	map->height = map_height(fd, map->width);
	ft_putstr_fd(ft_itoa(map->width), 1);
	ft_putstr_fd(ft_itoa(map->height), 1);
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