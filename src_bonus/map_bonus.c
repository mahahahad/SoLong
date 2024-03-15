/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:29 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 15:41:05 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_char(t_data *data, int x, int y)
{
	if ((int)ft_strlen(data->game->map->full[y]) != data->game->map->columns)
		return (ft_error("Map is not rectangular"));
	if (data->game->map->full[y][0] != '1'
		|| data->game->map->full[y][data->game->map->columns - 1] != '1')
		return (ft_error("Map must be surrounded by walls"));
	if ((y == 0 || y == data->game->map->rows - 1)
		&& data->game->map->full[y][x] != '1')
		return (ft_error("Map must be surrounded by walls"));
	else if (data->game->map->full[y][x] == 'C')
		data->game->collectables->total++;
	else if (data->game->map->full[y][x] == 'E')
		data->game->exit_count++;
	else if (data->game->map->full[y][x] == 'P')
		data->game->player_count++;
	else if (data->game->map->full[y][x] != '0'
		&& data->game->map->full[y][x] != '1')
		return (ft_error("Invalid character detected in map"));
	if (data->game->player_count > 1 || data->game->exit_count > 1)
		return (ft_error("Only one player and exit can be present in the map"));
	return (0);
}

/// @brief Check if the provided map is valid or not
/// @param data
// 	The data structure containing all the relevant game variables
/// @return
// 	Boolean if map is valid (0) or invalid (1)
int	check_map(t_data *data)
{
	int	res;
	int	y;
	int	x;

	y = 0;
	while (y < data->game->map->rows)
	{
		x = 0;
		while (x < data->game->map->columns)
		{
			res = check_char(data, x++, y);
			if (res)
				return (res);
		}
		y++;
	}
	if (!data->game->collectables->total || !data->game->exit_count
		|| !data->game->player_count)
		return (ft_error("At least one collectible, player, \
and exit must be present"));
	if (check_path(data, data->game->map->full) == false)
		return (ft_error("Player cannot reach the exit"));
	return (res);
}

/**
 * @brief
 * Read the map the file descriptor is pointing to and return it when finished.
 * Also sets the `data.game.map.full` variable
 * @param data
 * The data structure containing all the variables. But only depends on `data
 * game.map.fd`
 * @return int The status code. 0 if the map was read properly, 1 otherwise.
 */
int	read_map(t_data *data)
{
	char	*temp;
	char	*str;
	char	*map_full;

	temp = NULL;
	str = ft_strdup("");
	map_full = ft_strdup("");
	while (str)
	{
		free(str);
		str = get_next_line(data->game->map->fd);
		if (!str)
			break ;
		temp = map_full;
		map_full = ft_strjoin(map_full, str);
		free(temp);
		data->game->map->rows++;
	}
	if (!map_full[0])
		return (free(map_full), ft_error("Your map could not be opened"));
	data->game->map->full = ft_split(map_full, '\n');
	data->game->map->columns = ft_strlen(data->game->map->full[0]);
	free(map_full);
	return (close(data->game->map->fd), 0);
}
