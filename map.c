#include "so_long.h"

/**
 * @brief 
 * Read the map the file descriptor is pointing to and return it when finished. Also sets the `data.game.map.full` variable
 * @param data 
 * The data structure containing all the variables. But only depends on `data.game.map.fd`
 * @return int The status code. 0 if the map was read properly, 1 otherwise.
 */
int	read_map(t_data *data)
{
	char	*temp;
	char	*map_full;
	char	*str;
	int		fd;
	size_t 	prev_columns;

	str = NULL;
	temp = NULL;
	map_full = NULL;
	fd = data->game->map->fd;
	data->game->map->rows = 0;
	data->game->map->columns = 0;
	str = get_next_line(fd);
	prev_columns = ft_strlen(str);
	map_full = malloc(1);
	map_full[0] = '\0';
	temp = map_full;
	map_full = ft_strjoin(map_full, str);
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
