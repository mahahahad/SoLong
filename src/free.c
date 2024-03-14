/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:52:29 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/14 17:36:27 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void free_sprite(t_data *data, void *mlx_image)
{
	mlx_destroy_image(data->mlx_ptr, mlx_image);
}

void free_textures(t_data *data)
{
	if (have_textures_loaded(data))
	{
		free_sprite(data, data->game->textures->border_0);
		free_sprite(data, data->game->textures->border_1);
		free_sprite(data, data->game->textures->border_2);
		free_sprite(data, data->game->textures->border_3);
		free_sprite(data, data->game->textures->border_4);
		free_sprite(data, data->game->textures->border_5);
		free_sprite(data, data->game->textures->border_6);
		free_sprite(data, data->game->textures->border_7);
		free_sprite(data, data->game->textures->wall);
		free_sprite(data, data->game->textures->collectible);
		free_sprite(data, data->game->textures->empty);
		free_sprite(data, data->game->textures->exit);
		free_sprite(data, data->game->textures->player);
	}
	free(data->game->textures);
}

void free_data_struct(t_data *data)
{
	free(data->game->collectables);
	ft_free_2d_arr(data->game->map->full);
	free(data->game->map);
	free(data->game->player);
	free_textures(data);
	free(data->game);
	free(data->mlx_ptr);
	free(data);
}
