/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/07 15:56:35 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	render_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (y < data->game->map->rows)
	{
		x = -1;
		while (++x < data->game->map->columns)
			render_texture(data, check_texture(data, x, y), x, y);
		y++;
	}
	if (data->game->alien)
		display_enemy(data);
	display_moves(data);
	mlx_do_sync(data->mlx_ptr);
	return (0);
}

int	update_map(t_data *data)
{
	static int	frame;
	int			time_val;

	if (!frame)
		frame = clock();
	time_val = clock();
	if (time_val - frame > 50000)
	{
		data->game->textures->alien = data->game->textures->alien->next;
		data->game->textures->collectible
			= data->game->textures->collectible->next;
		data->game->textures->asteroid_1
			= data->game->textures->asteroid_1->next;
		data->game->textures->asteroid_2
			= data->game->textures->asteroid_2->next;
		data->game->textures->player = data->game->textures->player->next;
		frame = time_val;
	}
	render_map(data);
	return (0);
}
