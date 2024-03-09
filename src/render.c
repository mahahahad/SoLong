/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/09 13:38:10 by maabdull         ###   ########.fr       */
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
	if (data->game->enemy)
		display_enemy(data);
	display_moves(data);
	mlx_do_sync(data->mlx_ptr);
	return (0);
}

int	update_enemy_location(t_data *data)
{
	static int	frame;
	int			time_val;

	if (!frame)
		frame = clock();
	time_val = clock();
	if (time_val - frame > 100000)
	{
		move_enemy(data);
		frame = time_val;
	}
	return (0);
}

int	update_textures(t_data *data)
{
	static int	frame;
	int			time_val;

	if (!frame)
		frame = clock();
	time_val = clock();
	if (time_val - frame > 35000)
	{
		data->game->textures->player = data->game->textures->player->next;
		data->game->textures->enemy = data->game->textures->enemy->next;
		data->game->textures->collectible
			= data->game->textures->collectible->next;
		data->game->textures->wall = data->game->textures->wall->next;
		data->game->textures->exit = data->game->textures->exit->next;
		display_next_borders(data);
		frame = time_val;
	}
	return (0);
}

int	calculate_frame(t_data *data)
{
	update_textures(data);
	update_enemy_location(data);
	render_map(data);
	return (0);
}
