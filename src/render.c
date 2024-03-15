/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:49 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 15:41:26 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_do_sync(data->mlx_ptr);
	return (0);
}
