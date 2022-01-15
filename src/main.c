#include "so_long.h"

int	main(int argc, char **argv)
{
	printf("%d", ft_atoi("123"));
	t_data	data;
	ft_winsize(&data, argv);

	return (0);
}


void	ft_winsize(t_data *data, char **argv)
{
	int	fd;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		exit(EXIT_FAILURE);
	}
}

// waar komt EXIT_FAILURE vandaan?