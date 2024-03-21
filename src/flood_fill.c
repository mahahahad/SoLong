/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:37:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/21 13:44:56 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the given map contains characters that are not walls
 *
 * @param map
 * @return true
 * @return false
 */
bool	contains_only_walls(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != WALL)
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

void	fill_tile(char **map, int x, int y)
{
	if (map[y][x] == EXIT)
	{
		map[y][x] = WALL;
		return ;
	}
	if (map[y][x] == WALL)
		return ;
	else
		map[y][x] = WALL;
	fill_tile(map, x, y - 1);
	fill_tile(map, x + 1, y);
	fill_tile(map, x, y + 1);
	fill_tile(map, x - 1, y);
}

/**
 * @brief Replaces each non wall character that is reachable with a wall
 * At the end, checks if there are other characters remaining. If yes, those
 * characters are unreachable therefore map is invalid.
 *
 * @param data
 * @return int
 */
int	fill_map(t_data *data)
{
	int		x;
	int		y;
	char	**map_copy;

	x = 0;
	y = 0;
	ft_get_char_pos(data->game->map->full, PLAYER, &x, &y);
	map_copy = ft_tabdup(data->game->map->full);
	fill_tile(map_copy, x, y);
	if (!contains_only_walls(map_copy))
		return (ft_error("Invalid path (Player can't reach exit or\
 collectible)"));
	return (EXIT_SUCCESS);
}
