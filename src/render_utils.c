/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:53:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/14 15:33:52 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void render_texture(t_data *data, void *texture, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, texture, x * PLAYER_WIDTH + OFFSET, y * PLAYER_HEIGHT + OFFSET);
}

// Check which wall texture is supposed to be rendered in this position
void *check_wall_texture(t_data *data, int x, int y)
{
	if (y == 0)
		if (x == 0)
			return (data->game->textures->border_0);
		else if (x == data->game->map->columns - 1)
			return (data->game->textures->border_2);
		else
			return (data->game->textures->border_1);
	else if (y == data->game->map->rows - 1)
		if (x == 0)
			return (data->game->textures->border_6);
		else if (x == data->game->map->columns - 1)
			return (data->game->textures->border_4);
		else
			return (data->game->textures->border_5);
	else if (x == 0)
		return (data->game->textures->border_7);
	else if (x == data->game->map->columns - 1)
		return (data->game->textures->border_3);
	return (data->game->textures->wall);
}

void *check_texture(t_data *data, int x, int y)
{
	if (data->game->map->full[y][x] == WALL)
		return (check_wall_texture(data, x, y));
	if (data->game->map->full[y][x] == COLLECTIBLE)
		return (data->game->textures->collectible);
	if (data->game->map->full[y][x] == PLAYER)
		return (data->game->textures->player);
	if (data->game->map->full[y][x] == EXIT)
		return (data->game->textures->exit);
	return (data->game->textures->empty);
}

void display_moves(t_data *data)
{
	char *moves;
	char *str;

	moves = ft_itoa(data->game->move_count);
	str = ft_strjoin("Moves: ", moves);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 32, 0xFFFFFF, str);
	free(str);
	free(moves);
}
