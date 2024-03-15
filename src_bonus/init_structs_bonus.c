/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:04:33 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 15:41:05 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	init_map_struct(t_data *data)
{
	data->game->map = malloc(sizeof(t_map));
	if (!data->game->map)
		return (ft_error("The map struct could not be created"));
	data->game->map->columns = 0;
	data->game->map->rows = 0;
	data->game->map->fd = 0;
	data->game->map->full = NULL;
	return (0);
}

int	init_textures_struct(t_data *data)
{
	data->game->textures = malloc(sizeof(t_textures));
	if (!data->game->textures)
		return (ft_error("The textures struct could not be created"));
	data->game->textures->player = init_animated_sprite(*data,
			"textures/Player/");
	data->game->textures->collectible = init_animated_sprite(*data,
			"textures/Collectible/");
	data->game->textures->exit = init_animated_sprite(*data,
			"textures/Exit/");
	data->game->textures->empty = init_animated_sprite(*data,
			"textures/Empty/");
	data->game->textures->wall = init_animated_sprite(*data,
			"textures/Wall/");
	data->game->textures->enemy = init_animated_sprite(*data,
			"textures/Enemy/");
	load_borders(data);
	have_textures_loaded(data);
	return (0);
}

int	init_collectables_struct(t_data *data)
{
	data->game->collectables = malloc(sizeof(t_collectables));
	if (!data->game->collectables)
		return (ft_error("The collectables struct could not be created"));
	data->game->collectables->collected = 0;
	data->game->collectables->total = 0;
	return (0);
}

int	init_player_struct(t_data *data)
{
	data->game->player = malloc(sizeof(t_player));
	if (!data->game->player)
		return (ft_error("The player struct could not be created"));
	data->game->player->x = 0;
	data->game->player->y = 0;
	return (0);
}

int	init_data_struct(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("MLX could not be initialized"));
	data->game = malloc(sizeof(t_game));
	data->game->move_count = 0;
	data->game->player_count = 0;
	data->game->exit_count = 0;
	if (init_player_struct(data))
		return (free(data->game), free(data->mlx_ptr), exit(1), 1);
	if (init_collectables_struct(data))
		return (free(data->game->player), free(data->game), free(data->mlx_ptr),
			exit(1), 1);
	if (init_textures_struct(data))
		return (free(data->game->player), free(data->game->collectables),
			free(data->game), free(data->mlx_ptr), exit(1), 1);
	if (init_map_struct(data))
		return (free(data->game->player), free(data->game->collectables),
			free_textures(data), free(data->game), free(data->mlx_ptr), exit(1),
			1);
	data->game->enemy = NULL;
	return (0);
}
