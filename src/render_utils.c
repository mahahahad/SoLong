/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:53:20 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/07 15:53:49 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_texture(t_data *data, void *texture, int x, int y)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, texture, x
		* PLAYER_WIDTH + OFFSET, y * PLAYER_HEIGHT + OFFSET);
}

// Check which wall texture is supposed to be rendered in this position
void	*check_wall_texture(t_data *data, int x, int y)
{
	void	*corner;

	corner = data->game->textures->border->next->next->next->next->texture;
	if (y == 0)
		if (x == 0 || x == data->game->map->columns - 1)
			return (corner);
	else
		return (data->game->textures->border->texture);
	else if (y == data->game->map->rows - 1)
		if (x == 0 || x == data->game->map->columns - 1)
			return (corner);
	else
		return (data->game->textures->border->next->next->texture);
	else if (x == 0)
		return (data->game->textures->border->next->next->next->texture);
	else if (x == data->game->map->columns - 1)
		return (data->game->textures->border->next->texture);
	if (x % 2 == 0)
		return (data->game->textures->asteroid_2->texture);
	return (data->game->textures->asteroid_1->texture);
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
