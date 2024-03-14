/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:54:01 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/09 12:11:47 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_enemy(t_data *data)
{
	static bool	backwards;

	if (!data->game->enemy)
		return ;
	if (!data->game->enemy->path->prev_tile)
		backwards = false;
	if (!data->game->enemy->path->next_tile)
		backwards = true;
	if (backwards)
		data->game->enemy->path = data->game->enemy->path->prev_tile;
	else
		data->game->enemy->path = data->game->enemy->path->next_tile;
	if (data->game->enemy->path->current_tile->x == data->game->player->x
		&& data->game->enemy->path->current_tile->y == data->game->player->y)
	{
		ft_putstr_endl("You died bruh", 1);
		handle_destroy(data);
		return ;
	}
}

int	display_enemy(t_data *data)
{
	int	x;
	int	y;

	if (!data->game->enemy->path)
		return (1);
	x = data->game->enemy->path->current_tile->x;
	y = data->game->enemy->path->current_tile->y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game->textures->enemy->texture, x * PLAYER_WIDTH + OFFSET, y
		* PLAYER_HEIGHT + OFFSET);
	return (0);
}

/**
 * @brief Assign all of the tiles in the tiles array to the path structure->
 *
 * @param path The final path structure
 * @param tiles The tiles to be assigned to the path
 * @param tiles_size The size of the tiles array
 * @return int The status code of the assignment-> 0 if successful,
	1 otherwise->
 */
int	populate_path(t_path *path, t_tile *tiles[])
{
	int	i;

	i = 0;
	path->prev_tile = NULL;
	path->next_tile = NULL;
	while (tiles[i])
	{
		path->current_tile = tiles[i];
		path->next_tile = malloc(sizeof(t_path));
		path->next_tile->prev_tile = path;
		path = path->next_tile;
		i++;
	}
	path = path->prev_tile;
	free(path->next_tile);
	path->next_tile = NULL;
	while (--i > 0)
		path = path->prev_tile;
	return (0);
}

void	free_tiles(t_tile *tiles[])
{
	int	i;

	i = 0;
	while (tiles[i])
	{
		free(tiles[i]);
		i++;
	}
}

/**
 * @brief Initializes the enemy's patrol path by checking for free space around
 * the exit. Any side of the exit that has at least 2 empty spaces is
 * considered free space. Uses the first free sides found as the path if all
 * sides are not empty.
 *
 * @param data The data structure containing game variables
 * @return t_path The path of this enemy
 */
t_path	*initialize_enemy_path(t_data *data)
{
	int		exit_x;
	int		exit_y;
	t_path	*path;
	t_tile	*free_space_tiles[9];

	if (get_exit_coordinates(data, &exit_x, &exit_y) != 0)
		return (NULL);
	if (get_free_space(data, exit_x, exit_y, free_space_tiles) != 0)
		return (NULL);
	path = malloc(sizeof(t_path));
	populate_path(path, free_space_tiles);
	data->game->enemy = malloc(sizeof(t_enemy));
	data->game->enemy->path = path;
	return (path);
}
