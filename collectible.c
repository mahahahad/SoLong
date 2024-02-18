/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:28:02 by maabdull          #+#    #+#             */
/*   Updated: 2024/02/18 19:49:18 by maabdull         ###   ########.fr       */
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

t_sprite_animated	*init_collectible(t_data *data)
{
	void	*texture;
	char	*file_name;
	int		i;
	int		height;
	int		width;
	t_sprite_animated	*collectible;
	t_sprite_animated	*collectible_head;

	i = -1;
	height = PLAYER_HEIGHT;
	width = PLAYER_WIDTH;
	file_name = create_file_name("textures/Collectible/Collectible", ++i);
	texture = mlx_xpm_file_to_image(data->mlx_ptr, file_name, &width, &height);
	while (texture)
	{
		if (i == 0)
		{
			collectible = (t_sprite_animated *) malloc(sizeof(t_sprite_animated *));
			collectible_head = collectible;
		}
		collectible->texture = texture;
		collectible->next = (t_sprite_animated *) malloc(sizeof(t_sprite_animated *));
		collectible = collectible->next;
		file_name = create_file_name("textures/Collectible/Collectible", ++i);
		texture = mlx_xpm_file_to_image(data->mlx_ptr, file_name, &width, &height);
	}
	collectible->texture = collectible_head->texture;
	collectible->next = collectible_head->next;
	free(file_name);
	return (collectible);
}

int	main(void)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data *));
	data->game = (t_game *) malloc(sizeof(t_game *));
	data->game->textures = (t_textures *) malloc(sizeof(t_textures *));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1280, 720, "so_long");
	data->game->textures->collectible = init_collectible(data);
	while (data->game->textures->collectible)
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game->textures->collectible->texture, 0, 0);
			data->game->textures->collectible = data->game->textures->collectible->next;
			usleep(166667);
		}
	mlx_loop(data->mlx_ptr);
	free(data);
}

