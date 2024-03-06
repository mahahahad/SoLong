/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:50:08 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/05 18:32:58 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

// Initalize Texture pointers
void	init_sprites(t_data *data)
{
	data->game->textures->player = init_animated_sprite(*data,
			"textures/Player/Player");
	data->game->textures->collectible = init_animated_sprite(*data,
			"textures/Collectible/Collectible");
	data->game->textures->wall = init_animated_sprite(*data,
			"textures/Wall/SpaceRocks");
	data->game->textures->exit = init_animated_sprite(*data, "textures/Exit");
	data->game->textures->empty = init_animated_sprite(*data, "textures/Empty");
	data->game->textures->border = init_animated_sprite(*data,
			"textures/Border");
	data->game->textures->asteroid_1 = init_animated_sprite(*data,
			"textures/Asteroid1/Asteroid1");
	data->game->textures->asteroid_2 = init_animated_sprite(*data,
			"textures/Asteroid2/Asteroid2");
	data->game->textures->alien = init_animated_sprite(*data,
			"textures/Alien/Alien");
}

int	init_data_struct(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("MLX could not be initialized"));
	data->game = malloc(sizeof(t_game));
	data->game->textures = malloc(sizeof(t_textures));
	data->game->collectables = malloc(sizeof(t_collectables));
	data->game->player = malloc(sizeof(t_player));
	data->game->map = malloc(sizeof(t_map));
	data->game->alien = NULL;
	init_sprites(data);
	if (!data->game || !data->game->textures || !data->game->collectables
		|| !data->game->player || !data->game->map)
	{
		ft_error("Could not allocate enough space");
		exit(1);
		return (1);
	}
	return (0);
}

int	create_window(t_data *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, (data->game->map->columns + 2)
			* PLAYER_WIDTH, (data->game->map->rows + 2) * PLAYER_HEIGHT,
			"so_long");
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
		return (free_data_struct(data),
			ft_error("Your map could not be opened"));
	if (check_map(data))
		return (free_data_struct(data), ft_error("Your map is not valid"));
	create_window(data);
	initialize_enemy_path(data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, update_map, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
