/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:53:50 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 16:15:51 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	*create_texture(t_data data, char *file_name)
{
	void	*texture;
	int		height;
	int		width;

	height = PLAYER_HEIGHT;
	width = PLAYER_WIDTH;
	texture = mlx_xpm_file_to_image(data.mlx_ptr, file_name, &width, &height);
	return (texture);
}

bool	have_textures_loaded(t_data *data)
{
	if (data->game->textures->border_0 && data->game->textures->border_1
		&& data->game->textures->border_2 && data->game->textures->border_3
		&& data->game->textures->border_4 && data->game->textures->border_5
		&& data->game->textures->border_6 && data->game->textures->border_7
		&& data->game->textures->player && data->game->textures->empty
		&& data->game->textures->wall && data->game->textures->collectible
		&& data->game->textures->enemy)
		return (true);
	return (false);
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
