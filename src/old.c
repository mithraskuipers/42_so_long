static void	get_map_height(t_game *game)
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
		nbytes = read(game->map.fd, buff, 1);
		if (i == ((game->map.n_xtiles * TILE_WIDTH) / TILE_WIDTH))
		{
			count++;
			i = 0;
		}
		else
			i++;
	}
	game->map.n_ytiles = count;
}