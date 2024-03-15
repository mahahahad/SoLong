/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:53:50 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 16:14:41 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	data->game->textures->border_0 = create_texture(*data,
			"textures/Border0/0.xpm");
	data->game->textures->border_1 = create_texture(*data,
			"textures/Border1/0.xpm");
	data->game->textures->border_2 = create_texture(*data,
			"textures/Border2/0.xpm");
	data->game->textures->border_3 = create_texture(*data,
			"textures/Border3/0.xpm");
	data->game->textures->border_4 = create_texture(*data,
			"textures/Border4/0.xpm");
	data->game->textures->border_5 = create_texture(*data,
			"textures/Border5/0.xpm");
	data->game->textures->border_6 = create_texture(*data,
			"textures/Border6/0.xpm");
	data->game->textures->border_7 = create_texture(*data,
			"textures/Border7/0.xpm");
}
