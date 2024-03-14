/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:28:02 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/14 14:06:05 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
