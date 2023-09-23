#include "mlx_linux/mlx.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "so_long.h"

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*player;
	int	pos_x;
	int	pos_y;
	int	moves;
}		t_data;

static	int	ft_putnbr(int num)
{
	char	c;
	int 	len;
	
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

static	int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		write(1, &str[len++], 1);
	return (len);
}

// Functions to close the window cleanly
static int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

// Function to handle the keypresses
static int	handle_keypress(int keysym, t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (keysym == XK_Escape)
		handle_destroy(data);
	else if (keysym == XK_w)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player, data->pos_x, data->pos_y-=PLAYER_HEIGHT);
	else if (keysym == XK_a)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player, data->pos_x-=PLAYER_WIDTH, data->pos_y);
	else if (keysym == XK_s)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player, data->pos_x, data->pos_y+=PLAYER_HEIGHT);
	else if (keysym == XK_d)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->player, data->pos_x+=PLAYER_WIDTH, data->pos_y);
	else
		return (1);
	data->moves++;
	ft_putstr("You have made ");
	ft_putnbr(data->moves);
	ft_putstr(" moves so far\n");
	return (0);
}

// Function to check if the file extension is ".ber"
static int  check_ext(char *file)
{
	char    format[5];
	int i;
	int j;

	i = strlen(file) - 1;
	j = 3;
	strcpy(format, ".ber");
	while (format[j] == file[i--])
		j--;
	if (j < 0)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int	*width;
	int	*height;
	int	player_width;
	int	player_height;

	player_width = PLAYER_WIDTH;
	player_height = PLAYER_HEIGHT;
	width = &player_width;
	height = &player_height;

	if (argc != 2)
		return (ft_putstr("Error\nPlease enter the map you would like to use\n"), 1);
 	if (!check_ext(argv[1]))
 		return (ft_putstr("Error\nPlease input a map with a .ber file format\n"), 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	data.moves = 0;
	data.pos_x = 0;
	data.pos_y = 0;
	data.player = mlx_xpm_file_to_image(data.mlx_ptr, "textures/Player.xpm", width, height);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.player, data.pos_x, data.pos_y);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, ButtonPressMask, handle_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
