/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:53:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 15:41:05 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	render_texture(t_data *data, void *texture, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, texture, x
		* PLAYER_WIDTH + OFFSET, y * PLAYER_HEIGHT + OFFSET);
}

// Check which wall texture is supposed to be rendered in this position
void	*check_wall_texture(t_data *data, int x, int y)
{
	if (y == 0)
		if (x == 0)
			return (data->game->textures->border_0->texture);
	else if (x == data->game->map->columns - 1)
		return (data->game->textures->border_2->texture);
	else
		return (data->game->textures->border_1->texture);
	else if (y == data->game->map->rows - 1)
		if (x == 0)
			return (data->game->textures->border_6->texture);
	else if (x == data->game->map->columns - 1)
		return (data->game->textures->border_4->texture);
	else
		return (data->game->textures->border_5->texture);
	else if (x == 0)
		return (data->game->textures->border_7->texture);
	else if (x == data->game->map->columns - 1)
		return (data->game->textures->border_3->texture);
	return (data->game->textures->wall->texture);
}

void	*check_texture(t_data *data, int x, int y)
{
	if (data->game->map->full[y][x] == WALL)
		return (check_wall_texture(data, x, y));
	if (data->game->map->full[y][x] == COLLECTIBLE)
		return (data->game->textures->collectible->texture);
	if (data->game->map->full[y][x] == PLAYER)
		return (data->game->textures->player->texture);
	if (data->game->map->full[y][x] == EXIT)
		return (data->game->textures->exit->texture);
	return (data->game->textures->empty->texture);
}

void	display_moves(t_data *data)
{
	char	*moves;
	char	*str;

	moves = ft_itoa(data->game->move_count);
	str = ft_strjoin("Moves: ", moves);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 32, 0xFFFFFF, str);
	free(str);
	free(moves);
}

void	display_next_borders(t_data *data)
{
	data->game->textures->border_0 = data->game->textures->border_0->next;
	data->game->textures->border_1 = data->game->textures->border_1->next;
	data->game->textures->border_2 = data->game->textures->border_2->next;
	data->game->textures->border_3 = data->game->textures->border_3->next;
	data->game->textures->border_4 = data->game->textures->border_4->next;
	data->game->textures->border_5 = data->game->textures->border_5->next;
	data->game->textures->border_6 = data->game->textures->border_6->next;
	data->game->textures->border_7 = data->game->textures->border_7->next;
}
