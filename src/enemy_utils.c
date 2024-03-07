/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:04:56 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/06 18:36:09 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Get the coordinates of the exit from the map string double pointer
 * in the data struct. Sets the x and y parameters to contain these coordinates
 *
 * @param data The data structure containing the game variables
 * @param x The x coordinate of the exit
 * @param y The y coordinate of the exit
 * @return int The status code. 0 if exit was found, 1 otherwise.
 */
int	get_exit_coordinates(t_data *data, int *x, int *y)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->game->map->full[j])
	{
		i = 0;
		while (data->game->map->full[j][i])
		{
			if (data->game->map->full[j][i] == EXIT)
			{
				*x = i;
				*y = j;
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

void	set_delta_values(int delta[], char axis)
{
	if (axis == 'x')
	{
		delta[0] = -1;
		delta[1] = 0;
		delta[2] = 1;
		delta[3] = 1;
		delta[4] = 1;
		delta[5] = 0;
		delta[6] = -1;
		delta[7] = -1;
	}
	else
	{
		delta[0] = -1;
		delta[1] = -1;
		delta[2] = -1;
		delta[3] = 0;
		delta[4] = 1;
		delta[5] = 1;
		delta[6] = 1;
		delta[7] = 0;
	}
}

void	reset_free_tiles(t_tile *tiles[], int *free_tiles_found)
{
	int	i;

	i = 0;
	if (*free_tiles_found > 1)
		return ;
	while (i < *free_tiles_found)
		free(tiles[i++]);
	*free_tiles_found = 0;
}

/**
 * @brief Creates a new t_tile struct and assigns it the provided
 * x and y coordinates and appends this tile to the tiles list
 *
 * @param tiles The list of tiles to append to
 * @param x The x coordinate of the new tile
 * @param y The y coordinate of the new tile
 */
void	append_tile(t_tile *tiles[], int x, int y, int *free_tiles_found)
{
	t_tile	*free_tile;

	free_tile = malloc(sizeof(t_tile));
	if (!free_tile)
	{
		ft_error("Could not allocate space");
		return ;
	}
	free_tile->x = x;
	free_tile->y = y;
	tiles[(*free_tiles_found)++] = free_tile;
}

/**
 * @brief Gets the free space around the specified coordinates.
 * If atleast 2 tiles on one side are empty tiles, they are considered
 * free space. Goes in the order Top->Right->Bottom->Left
 *
 * @param data The data structure containing all the game variables
 * @param x The x coordinate of the anchor
 * @param y The y coordinate of the anchor
 * @param free_space[] The free tiles surrounding the object
 * @param size The number of free tiles surround the object
 * @return int The status code, 0 if atleast 2 empty spaces were found,
 * 1 otherwise
 */
int	get_free_space(t_data *data, int x, int y, t_tile *free_space[])
{
	int		dx[8];
	int		dy[8];
	int		free_tiles_found;
	int		i;

	i = 0;
	free_tiles_found = 0;
	set_delta_values(dx, 'x');
	set_delta_values(dy, 'y');
	while (i < 8)
	{
		if (data->game->map->full[y + dy[i]][x + dx[i]] == EMPTY)
			append_tile(free_space, x + dx[i], y + dy[i], &free_tiles_found);
		else
			reset_free_tiles(free_space, &free_tiles_found);
		i++;
	}
	if (free_tiles_found < 2)
		return (reset_free_tiles(free_space, &free_tiles_found), 1);
	free_space[free_tiles_found] = NULL;
	return (0);
}
