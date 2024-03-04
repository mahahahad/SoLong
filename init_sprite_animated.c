/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_animated.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:28:02 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/04 11:37:53 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*create_file_name(char *dir, int i)
{
	char	*num;
	char	*temp;
	char	*file_name;

	num = ft_itoa(i);
	temp = ft_strjoin(dir, num);
	free(num);
	file_name = ft_strjoin(temp, ".xpm");
	free(temp);
	return (file_name);
}

/**
 * @brief Initializes a linked list containing all the texture frames of the sprite
 * 
 * @param data The data structure containing mlx_ptr and game strucs
 * @param sprite_textures_dir The directory containing this sprites texture 
 * files. Expects numbered frames in the format: `dir/prefix` resulting in
 * `dir/prefix(0).xpm`
 * @return t_sprite_animated* The animated sprite containing the current frames texture and the next frames' textures for easy animating
 */
t_sprite_animated	*init_animated_sprite(t_data data, char *sprite_textures_dir)
{
	void	*texture;
	char	*file_name;
	int		i;
	int		height;
	int		width;
	t_sprite_animated	*sprite;
	t_sprite_animated	*sprite_head;

	i = -1;
	height = PLAYER_HEIGHT;
	width = PLAYER_WIDTH;
	file_name = create_file_name(sprite_textures_dir, ++i);
	texture = mlx_xpm_file_to_image(data.mlx_ptr, file_name, &width, &height);
	while (texture)
	{
		if (i == 0)
		{
			sprite = malloc(sizeof(t_sprite_animated));
			sprite_head = sprite;
		}
		sprite->texture = texture;
		sprite->next = malloc(sizeof(t_sprite_animated));
		sprite = sprite->next;
		file_name = create_file_name(sprite_textures_dir, ++i);
		texture = mlx_xpm_file_to_image(data.mlx_ptr, file_name, &width, &height);
	}
	sprite->texture = sprite_head->texture;
	sprite->next = sprite_head->next;
	free(file_name);
	return (sprite);
}

// int	main(void)
// {
// 	t_data	*data;

// 	data = (t_data *) malloc(sizeof(t_data *));
// 	data->game = (t_game *) malloc(sizeof(t_game *));
// 	data->game->textures = (t_textures *) malloc(sizeof(t_textures *));
// 	data->mlx_ptr = mlx_init();
// 	data->win_ptr = mlx_new_window(data->mlx_ptr, 1280, 720, "so_long");
// 	data->game->textures->collectible = init_animated_sprite(data, "textures/Wall/SpaceRocks");
// 	while (data->game->textures->collectible)
// 		{
// 			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game->textures->collectible->texture, 0, 0);
// 			data->game->textures->collectible = data->game->textures->collectible->next;
// 			usleep(166667);
// 		}
// 	mlx_loop(data->mlx_ptr);
// 	free(data);
// }

