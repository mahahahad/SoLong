/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/05 15:50:13 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	render_map(t_data *data)
{
	int		x;
	int		y;
	int		offset_x;
	int		offset_y;
	char	*moves;
	char	*str;

	x = 0;
	y = 0;
	offset_x = 64;
	offset_y = 64;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (y < data->game->map->rows)
	{
		while (x < data->game->map->columns)
		{
			if (data->game->map->full[y][x] == WALL)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->border->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
				if (y > 0)
				{
					if (y == data->game->map->rows - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
						data->game->textures->border->next->next->texture, \
						x * PLAYER_WIDTH + offset_x, \
						y * PLAYER_HEIGHT + offset_y);
					else if (x == 0)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
						data->game->textures->border->next->next->next->texture, \
						x * PLAYER_WIDTH + offset_x, \
						y * PLAYER_HEIGHT + offset_y);
					else if (x == data->game->map->columns - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
						data->game->textures->border->next->texture, \
						x * PLAYER_WIDTH + offset_x, \
						y * PLAYER_HEIGHT + offset_y);
					else
					{
						if ((x % 2) == 0)
							mlx_put_image_to_window(data->mlx_ptr, \
							data->win_ptr, \
							data->game->textures->asteroid_2->texture, \
							x * PLAYER_WIDTH + offset_x, \
							y * PLAYER_HEIGHT + offset_y);
						else
							mlx_put_image_to_window(data->mlx_ptr, \
							data->win_ptr, \
							data->game->textures->asteroid_1->texture, \
							x * PLAYER_WIDTH + offset_x, \
							y * PLAYER_HEIGHT + offset_y);
					}
				}
				if ((x == 0 && y == 0) || \
					(x == data->game->map->columns - 1 && \
					y == data->game->map->rows - 1) || \
					(x == 0 && y == data->game->map->rows - 1) || \
					(x == data->game->map->columns - 1 && y == 0))
					mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->border->next->next->next->next->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == EMPTY)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->empty->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
			if (data->game->map->full[y][x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->collectible->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == PLAYER)
			{
				data->game->player->x = x;
				data->game->player->y = y;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->player->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == EXIT)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, \
				data->game->textures->exit->texture, \
				x * PLAYER_WIDTH + offset_x, \
				y * PLAYER_HEIGHT + offset_y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (data->game->alien)
		display_enemy(data);
	moves = ft_itoa(data->game->moves);
	str = ft_strjoin("Moves: ", moves);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 32, 0xFFFFFF, str);
	// mlx_do_sync(data->mlx_ptr);
	free(str);
	free(moves);
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
		data->game->textures->collectible = \
		data->game->textures->collectible->next;
		data->game->textures->asteroid_1 = \
		data->game->textures->asteroid_1->next;
		data->game->textures->asteroid_2 = \
		data->game->textures->asteroid_2->next;
		data->game->textures->player = data->game->textures->player->next;
		frame = time_val;
	}
	render_map(data);
	return (0);
}
