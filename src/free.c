/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:52:29 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/06 21:50:46 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_alien_path(t_data *data)
{
	t_path	*current;

	current = data->game->alien->path;
	if (!data->game->alien)
		return ;
	while (current && current->next_tile)
		current = current->next_tile;
	while (current && current->prev_tile)
	{
		current = current->prev_tile;
		free(current->next_tile->current_tile);
		current->next_tile->current_tile = NULL;
		free(current->next_tile);
		current->next_tile = NULL;
	}
	free(current->current_tile);
	current->current_tile = NULL;
	free(current);
	current = NULL;
}

// static void	free_animated_sprite(t_data *data, t_sprite_animated *sprite)
// {
// 	t_sprite_animated	*temp;
// 	t_sprite_animated	*first;

// 	first = sprite;
// 	while (sprite->texture != first->texture)
// 	{
// 		temp = sprite->next;
// 		mlx_destroy_image(data->mlx_ptr, sprite->texture);
// 		free(sprite);
// 		sprite = NULL;
// 		sprite = temp;
// 	}
// 	free(first);
// }

static void	free_sprite(t_data *data, t_sprite_animated *sprite_head)
{
	t_sprite_animated	*current;
	t_sprite_animated	*next;

	current = sprite_head;
	if (!current)
		return ;
	next = current->next;
	while (next != sprite_head)
	{
		next = current->next;
		if (current->texture)
			mlx_destroy_image(data->mlx_ptr, current->texture);
		free(current);
		current = next;
		next = current->next;
	}
	if (current->texture)
		mlx_destroy_image(data->mlx_ptr, current->texture);
	free(current);
}

void	free_textures(t_data *data)
{
	if (data->game->textures->alien->texture)
	{
		free_sprite(data, data->game->textures->alien);
		free_sprite(data, data->game->textures->asteroid_1);
		free_sprite(data, data->game->textures->asteroid_2);
		free_sprite(data, data->game->textures->border);
		free_sprite(data, data->game->textures->collectible);
		free_sprite(data, data->game->textures->empty);
		free_sprite(data, data->game->textures->exit);
		free_sprite(data, data->game->textures->player);
		free_sprite(data, data->game->textures->wall);
	}
	free(data->game->textures);
}

void	free_data_struct(t_data *data)
{
	free(data->game->collectables);
	ft_free_2d_arr(data->game->map->full);
	free(data->game->map);
	free(data->game->player);
	free_textures(data);
	if (data->game->alien)
	{
		free_alien_path(data);
		free(data->game->alien);
		data->game->alien = NULL;
	}
	free(data->game);
	free(data->mlx_ptr);
	free(data);
}
