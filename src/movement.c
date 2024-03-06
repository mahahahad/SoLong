/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:34:03 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/06 17:56:10 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_data *data, int new_x, int new_y)
{
	data->game->map->full[data->game->player->y][data->game->player->x] = '0';
	data->game->player->x = new_x;
	data->game->player->y = new_y;
	data->game->map->full[new_y][new_x] = 'P';
	data->game->moves++;
	ft_putstr("You have made ");
	ft_putnbr(data->game->moves);
	ft_putstr(" moves so far\n");
}

bool	can_exit(t_data *data)
{
	if (data->game->collectables->collected == data->game->collectables->total)
	{
		ft_putstr_endl("Ws in the shaaaat!!!!", 1);
		handle_destroy(data);
		return (0);
	}
	return (1);
}

int	move_to(t_data *data, int new_x, int new_y)
{
	if (data->game->map->full[new_y][new_x] == '1')
		return (1);
	else if (data->game->map->full[new_y][new_x] == 'C')
		++data->game->collectables->collected;
	else if (data->game->map->full[new_y][new_x] == 'E')
		return (can_exit(data));
	else if (data->game->alien
		&& new_y == data->game->alien->path->current_tile->y
		&& new_x == data->game->alien->path->current_tile->x)
	{
		ft_putstr("You died bruh\n");
		handle_destroy(data);
		return (0);
	}
	move_player(data, new_x, new_y);
	return (0);
}
