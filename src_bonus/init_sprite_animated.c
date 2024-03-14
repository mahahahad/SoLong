/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_animated.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 16:28:02 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/14 21:00:56 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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

t_sprite	*append_to_list(t_sprite *head, void *texture)
{
	t_sprite	*new_node;
	t_sprite	*temp;

	new_node = malloc(sizeof(t_sprite));
	new_node->texture = texture;
	if (!head)
	{
		new_node->next = new_node;
		return (new_node);
	}
	temp = head;
	while (temp->next != head)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = head;
	return (head);
}

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

/**
 * @brief Initializes a linked list containing all the texture frames of the
 * sprite
 *
 * @param data The data structure containing mlx_ptr and game strucs
 * @param sprite_textures_dir The directory containing this sprites texture
 * files. Expects numbered frames in the format: `dir/prefix` resulting in
 * `dir/prefix/(0).xpm`
 * @return t_sprite_animated* The animated sprite containing the current frames
 * texture and the next frames' textures for easy animating
 */
t_sprite	*init_animated_sprite(t_data data,
		char *sprite_textures_dir)
{
	void		*texture;
	char		*file_name;
	int			i;
	t_sprite	*sprite_head;

	i = -1;
	sprite_head = NULL;
	while (1)
	{
		file_name = create_file_name(sprite_textures_dir, ++i);
		texture = create_texture(data, file_name);
		free(file_name);
		if (!texture)
			break ;
		sprite_head = append_to_list(sprite_head, texture);
	}
	return (sprite_head);
}
