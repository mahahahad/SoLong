/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:47:59 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 16:07:26 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	create_window(t_data *data)
{
	int	width;
	int	height;
	int	screen_x;
	int	screen_y;

	width = data->game->map->columns * PLAYER_WIDTH + (OFFSET * 2);
	height = data->game->map->rows * PLAYER_HEIGHT + (OFFSET * 2);
	mlx_get_screen_size(data->mlx_ptr, &screen_x, &screen_y);
	if (width > screen_x || height > screen_y)
		return (free_data_struct(data), ft_error("Map is too large"), exit(1),
			1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "so_long");
	if (!data->win_ptr)
	{
		free_data_struct(data);
		ft_error("Window could not be created");
		exit(1);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	parse_args(argc, argv);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Could not allocate enough space"));
	init_data_struct(data);
	data->game->map->fd = open(argv[1], O_RDONLY);
	if (read_map(data))
		return (free_data_struct(data), 1);
	if (check_map(data))
		return (free_data_struct(data), 1);
	create_window(data);
	initialize_enemy_path(data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, calculate_frame, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
