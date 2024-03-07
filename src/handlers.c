/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:23:27 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/06 18:59:54 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data_struct(data);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC || keysym == KEY_Q)
		return (handle_destroy(data), 0);
	else
	{
		if (data->game->alien)
			move_enemy(data);
		if (keysym == KEY_W || keysym == KEY_ARROW_UP)
			move_to(data, data->game->player->x, data->game->player->y - 1);
		else if (keysym == KEY_A || keysym == KEY_ARROW_LEFT)
			move_to(data, data->game->player->x - 1, data->game->player->y);
		else if (keysym == KEY_S || keysym == KEY_ARROW_DOWN)
			move_to(data, data->game->player->x, data->game->player->y + 1);
		else if (keysym == KEY_D || keysym == KEY_ARROW_RIGHT)
			move_to(data, data->game->player->x + 1, data->game->player->y);
		else
			return (1);
	}
	return (0);
}
