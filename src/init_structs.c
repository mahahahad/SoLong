/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 21:04:33 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 16:14:59 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	data->game->textures->player = create_texture(*data,
			"textures/Player/0.xpm");
	data->game->textures->collectible = create_texture(*data,
			"textures/Collectible/0.xpm");
	data->game->textures->exit = create_texture(*data, "textures/Exit/0.xpm");
	data->game->textures->empty = create_texture(*data, "textures/Empty/0.xpm");
	data->game->textures->wall = create_texture(*data, "textures/Wall/0.xpm");
	data->game->textures->enemy = create_texture(*data, "textures/Enemy/0.xpm");
	load_borders(data);
	if (!have_textures_loaded(data))
		return (ft_error("The textures could not be loaded"));
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
	data->win_ptr = NULL;
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
	return (EXIT_SUCCESS);
}
