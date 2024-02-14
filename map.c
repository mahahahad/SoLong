#include "so_long.h"

/**
 * @brief 
 * Read the map the file descriptor is pointing to and return it when finished. Also sets the `data.game.map.full` variable
 * @param data 
 * The data structure containing all the variables. But only depends on `data.game.map.fd`
 * @return char* map_full:
 * The complete map as a string, seperated by newlines, or NULL if the map is invalid
 */
char	*read_map(t_data *data)
{
	char	*temp;
	char	*map_full;
	char	*str;
	int		fd;
	size_t 	prev_columns;

	str = NULL;
	temp = NULL;
	map_full = NULL;
	fd = data->game.map.fd;
	data->game.map.rows = 0;
	data->game.map.columns = 0;
	str = get_next_line(fd);
	prev_columns = ft_strlen(str);
	map_full = malloc(1);
	temp = map_full;
	map_full = ft_strjoin(map_full, str);
	free(temp);
	temp = NULL;
	while (str != NULL)
	{
		str = get_next_line(fd);
		if (ft_strlen(str) && prev_columns != ft_strlen(str))
			return (ft_putstr("Your map is not rectangular\n"),
					free(str),
					free(map_full),
					NULL);
		data->game.map.rows++;
		if (str == NULL)
			break ;
		temp = map_full;
		map_full = ft_strjoin(map_full, str);
		free(temp);
		temp = NULL;
	}
	free(str);
	str = NULL;
	data->game.map.full = ft_split(map_full, '\n');
	data->game.map.columns = ft_strlen(data->game.map.full[0]);
	// TODO: Remove
	print_arr(data->game.map.full, data->game.map.rows, data->game.map.columns);
	return (close(fd), map_full);
}
