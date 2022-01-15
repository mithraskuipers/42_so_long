#include "so_long.h"




#define EXIT_FAIL 1

void	ft_winsize(t_data *data, char **argv)
{
	int	fd;


	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("hey");
		//exit(EXIT_FAIL);
	}
	data->size_x = 2;
	data->size_y = 2;
}




int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
	{
		exit(EXIT_FAIL);
	}

	printf("%d", ft_atoi("123"));
	ft_winsize(&data, argv);
	printf("%d", data.size_x);
	return (0);
}

// waar komt EXIT_FAILURE vandaan?