#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}		t_data;

int	handle_keypress(int keysym, t_data *data)
{
	(void) data;
	printf("You pressed: %d\n", keysym);
	return (0);
}

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "MLX Window");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &handle_destroy, &data);
	mlx_loop(data.win_ptr);
	return (0);
}
