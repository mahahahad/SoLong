#include "mlx_mac/mlx.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <X11/X.h>
//#include <X11/keysym.h>
#include "so_long.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_data;

typedef struct g_data
{
	void	*player;
	void	*empty;
	void	*wall;
	void	*collectable;
	void	*exit;
	int		map;
	int		pos_x;
	int		pos_y;
	int		moves;
}			game_data;

static int	ft_putnbr(int num)
{
	char	c;
	int		len;

	len = 0;
	if (num < 0)
	{
		len += write(1, "-", 1);
		if (num <= INT_MIN)
			return (len += ft_putnbr(-num / 10), len += ft_putnbr(8));
		ft_putnbr(-num);
		return (len);
	}
	if (num >= 10)
		len += ft_putnbr(num / 10);
	c = (num % 10) + '0';
	len += write(1, &c, 1);
	return (len);
}

static int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		write(1, &str[len++], 1);
	return (len);
}

int	render_map(t_data *data, game_data *game)
{
	int		output;
	char	*buffer;

	output = 1;
	buffer = malloc(1);
	while (output)
	{
		output = read(game->map, buffer, 1);
		if (output < 0)
			return (free(buffer), -1);
		if (output == 0)
			break ;
		if (buffer[0] == '\n')
		{
			game->pos_x = 0;
			game->pos_y += PLAYER_HEIGHT;
			continue ;
		}
		if (buffer[0] == '0')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, game->empty,
				game->pos_x, game->pos_y);
		if (buffer[0] == '1')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, game->wall,
				game->pos_x, game->pos_y);
		if (buffer[0] == 'P')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, game->player,
				game->pos_x, game->pos_y);
		if (buffer[0] == 'E')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, game->exit,
				game->pos_x, game->pos_y);
		if (buffer[0] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				game->collectable, game->pos_x, game->pos_y);
		game->pos_x += PLAYER_WIDTH;
	}
	return (free(buffer), 0);
}
// Functions to close the window cleanly
static int	handle_destroy(t_data *data, game_data *game)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	close(game->map);
	exit(0);
	return (0);
}

// Function to handle the keypresses
static int	handle_keypress(int keysym, t_data *data, game_data *game)
{
	if (keysym == 53)
		handle_destroy(data, game);
	render_map(data, game);
	/*
		else if (keysym == XK_w)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player,
			data->pos_x, data->pos_y-=PLAYER_HEIGHT);
		else if (keysym == XK_a)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player,
			data->pos_x-=PLAYER_WIDTH, data->pos_y);
		else if (keysym == XK_s)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player,
			data->pos_x, data->pos_y+=PLAYER_HEIGHT);
		else if (keysym == XK_d)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player,
			data->pos_x+=PLAYER_WIDTH, data->pos_y);
		else
		return (1);
		*/
	game->moves++;
	ft_putstr("You have made ");
	ft_putnbr(game->moves);
	ft_putstr(" moves so far\n");
	return (0);
}

// Function to check if the file extension is ".ber"
static int	check_ext(char *file)
{
	char	format[5];
	int		i;
	int		j;

	i = strlen(file) - 1;
	j = 3;
	strcpy(format, ".ber");
	while (format[j] == file[i--])
		j--;
	if (j < 0)
		return (1);
	return (0);
}

static int	get_map_height(int fd)
{
	int		output;
	int		height;
	char	buf[1];

	output = 1;
	height = 0;
	buf[0] = '\0';
	while (output != 0)
	{
		output = read(fd, buf, 1);
		if (buf[0] == '\n')
			height++;
	}
	return (height);
}

static int	get_map_width(int fd)
{
	char	buf[2];
	int		output;
	int		width;

	buf[1] = '\0';
	output = 1;
	width = 0;
	while (output != 0)
	{
		output = read(fd, buf, 1);
		if (buf[0] == '\n')
			break ;
		width++;
	}
	return (width);
}

int	main(int argc, char *argv[])
{
	t_data		data;
	game_data	game;
	int			*width;
	int			*height;
	int			player_width;
	int			player_height;
	int			map_width;
	int			map_height;

	player_width = PLAYER_WIDTH;
	player_height = PLAYER_HEIGHT;
	width = &player_width;
	height = &player_height;
	if (argc != 2)
		return (ft_putstr("Error\nPlease enter the map you would like to use\n"),
			1);
	if (!check_ext(argv[1]))
		return (ft_putstr("Error\nPlease input a map with a .ber file format\n"),
			1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	game.map = open(argv[1], O_RDONLY);
	map_width = get_map_width(game.map) * PLAYER_WIDTH;
	map_height = get_map_height(game.map) * PLAYER_HEIGHT;
	close(game.map);
	game.map = open(argv[1], O_RDONLY);
	data.win_ptr = mlx_new_window(data.mlx_ptr, map_width, map_height,
		"so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	game.moves = 0;
	game.pos_x = 0;
	game.pos_y = 0;
	game.player = mlx_xpm_file_to_image(data.mlx_ptr, "textures/Player.xpm",
		width, height);
	game.empty = mlx_xpm_file_to_image(data.mlx_ptr, "textures/Empty.xpm",
		width, height);
	game.exit = mlx_xpm_file_to_image(data.mlx_ptr, "textures/Spaceship.xpm",
		width, height);
	game.collectable = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Tablet.xpm", width, height);
	game.wall = mlx_xpm_file_to_image(data.mlx_ptr, "textures/Border.xpm",
		width, height);
	render_map(&data, &game);
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.player,
	// 	data.pos_x, data.pos_y);
	mlx_hook(data.win_ptr, 2, 1L << 17, handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
