/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:53:50 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/09 11:17:48 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

bool	have_textures_loaded(t_data *data)
{
	(void) data;
	return (true);
}

void	load_borders(t_data *data)
{
	data->game->textures->border_0 = init_animated_sprite(*data,
			"textures/Border0/");
	data->game->textures->border_1 = init_animated_sprite(*data,
			"textures/Border1/");
	data->game->textures->border_2 = init_animated_sprite(*data,
			"textures/Border2/");
	data->game->textures->border_3 = init_animated_sprite(*data,
			"textures/Border3/");
	data->game->textures->border_4 = init_animated_sprite(*data,
			"textures/Border4/");
	data->game->textures->border_5 = init_animated_sprite(*data,
			"textures/Border5/");
	data->game->textures->border_6 = init_animated_sprite(*data,
			"textures/Border6/");
	data->game->textures->border_7 = init_animated_sprite(*data,
			"textures/Border7/");
}
