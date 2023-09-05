#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}		t_data;

static int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

static int	handle_keypress(int keysym, t_data *data)
{
	(void) data;
	printf("You pressed: %d\n", keysym);
	if (keysym == XK_Escape)
		handle_destroy(data);
	return (0);
}

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
	(void) argv;

	if (argc != 2)
		return (printf("Please enter the map you would like to use"), 1);
 	if (!check_ext(argv[1]))
 		return (printf("Please input a map with a .ber format"), 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, ButtonPressMask, handle_destroy, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
