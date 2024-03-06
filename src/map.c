/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:51:29 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/05 17:08:54 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/// @brief Check if the provided map is valid or not
/// @param data
// 	The data structure containing all the relevant game variables
/// @return
// 	Boolean if map is valid (0) or invalid (1)
int	check_map(t_data *data)
{
	int		y;
	int		x;
	int		exit_count;
	int		player_count;

	y = 0;
	exit_count = 0;
	player_count = 0;
	data->game->collectables->total = 0;
	data->game->collectables->collected = 0;
	data->game->moves = 0;
	while (y < data->game->map->rows)
	{
		x = 0;
		if (data->game->map->full[y][0] != '1' || \
			data->game->map->full[y][data->game->map->columns - 1] != '1')
			return (ft_error("Map must be surrounded by walls"));
		while (x < data->game->map->columns)
		{
			if ((y == 0 || y == data->game->map->rows - 1) && \
				data->game->map->full[y][x] != '1')
				return (ft_error("Map must be surrounded by walls"));
			else if (data->game->map->full[y][x] == 'C')
				data->game->collectables->total++;
			else if (data->game->map->full[y][x] == 'E')
				exit_count++;
			else if (data->game->map->full[y][x] == 'P')
				player_count++;
			else if (data->game->map->full[y][x] != '0' && \
					data->game->map->full[y][x] != '1')
			{
				ft_error("Invalid character detected in map: ");
				write(1, &data->game->map->full[y][x], 1);
				ft_putstr("\n");
				exit(1);
				return (1);
			}
			x++;
		}
		y++;
	}
	if (data->game->collectables->total == 0)
		return (ft_error("At least one collectible must be present"));
	if (exit_count != 1)
		return (ft_error("Only one exit can be present"));
	if (player_count != 1)
		return (ft_error("Only one player can be present"));
	if (check_path(data->game->map->full) == false)
		return (ft_error("Player cannot reach the exit"));
	return (0);
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
	char	*map_full;
	char	*str;
	int		fd;
	size_t	prev_columns;

	str = NULL;
	temp = NULL;
	map_full = NULL;
	fd = data->game->map->fd;
	data->game->map->rows = 0;
	data->game->map->columns = 0;
	data->game->map->full = NULL;
	str = get_next_line(fd);
	if (!str)
		return (1);
	prev_columns = ft_strlen(str);
	map_full = malloc(1);
	map_full[0] = '\0';
	temp = map_full;
	map_full = ft_strjoin(map_full, str);
	free(str);
	free(temp);
	temp = NULL;
	while (str != NULL)
	{
		str = get_next_line(fd);
		if (ft_strlen(str) && prev_columns != ft_strlen(str))
			return (free(str),
				free(map_full),
				ft_error("Your map is not rectangular"));
		data->game->map->rows++;
		if (str == NULL)
			break ;
		temp = map_full;
		map_full = ft_strjoin(map_full, str);
		free(str);
		free(temp);
		temp = NULL;
	}
	free(str);
	str = NULL;
	data->game->map->full = ft_split(map_full, '\n');
	data->game->map->columns = ft_strlen(data->game->map->full[0]);
	free(map_full);
	return (close(fd), 0);
}
