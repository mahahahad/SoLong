/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:50:08 by maabdull          #+#    #+#             */
/*   Updated: 2023/11/12 13:29:07by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_ext(char *file)
{
	char	format[5];
	int		i;
	int		j;

	i = strlen(file) - 1;
	j = 3;
	strcpy(format, ".ber");
	while (format[j] == file[i--])
		j--;
	if (j < 0)
		return (1);
	return (0);
}

/// @brief Read the map the file descriptor is pointing to and return it when finished
/// @param fd
// The file descriptor that points to the map to read
/// @return
// The complete map as a string, seperated by newlines
char	*read_map(int fd)
{
	char	*map_full;
	char	*str;

	str = NULL;
	map_full = NULL;
	ft_putstr("Something is cooking...\n");
	str = get_next_line(fd);
	map_full = malloc(1);
	// TODO: LEAKS
	map_full = ft_strjoin(map_full, str);
	while (str != NULL)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		// TODO: LEAKS
		map_full = ft_strjoin(map_full, str);
	}
	return (close(fd), map_full);
}

/// @brief Count the number of columns in the provided map
/// @param map The map to count
/// @return The number of columns INCLUDING THE NEWLINE CHARACTER
static int	count_columns(char *map)
{
	int	columns;

	columns = 0;
	while (map[columns] != '\n')
		columns++;
	return (++columns);
}

/// @brief Gets the width and height of the provided map
/// @param map The map to measure
/// @param height The variable that will contain the height
/// @param width The variable that will contain the width
void	get_map_size(char *map, int *height, int *width)
{
	int	columns;
	int	rows;

	columns = 0;
	rows = 0;
	while (map[columns] != '\n')
		columns++;
	while (map[rows] != '\0')
		rows += columns + 1;
	*height = columns;
	*width = rows / columns;
}

/// @brief Check if the provided map is valid or not
/// @param map
// 	The complete map provided as a string
/// @return
// Boolean if map is valid (0) or invalid (1)
int	check_map(char *map)
{
	int	is_valid;
	int	map_width;

	is_valid = 0;
	map_width = count_columns(map);
	if (ft_strlen(map) % map_width == 0)
		is_valid = 0;
	else
		is_valid = 1;
	return (is_valid);
}

void	render_map(char *map, t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	x = 0;
	y = 0;
	while (map[++i] != 0)
	{
		if (map[i] == '\n')
		{
			x = 0;
			y += PLAYER_HEIGHT;
			continue ;
		}
		if (map[i] == '1')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->game.wall_texture, x, y);
		if (map[i] == '0')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->game.empty_texture, x, y);
		if (map[i] == 'C')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->game.collectable_texture, x, y);
		if (map[i] == 'P')
		{
			data->game.player.player_pos_x = x;
			data->game.player.player_pos_y = y;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->game.player_texture, x, y);
		}
		if (map[i] == 'E')
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->game.exit_texture, x, y);
		x += PLAYER_WIDTH;
	}
}

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 53)
		return (handle_destroy(data), 0);
	if (keysym == 13)
		data->game.player.player_pos_y -= PLAYER_HEIGHT;
	if (keysym == 0)
		data->game.player.player_pos_x -= PLAYER_WIDTH;
	if (keysym == 1)
		data->game.player.player_pos_y += PLAYER_HEIGHT;
	if (keysym == 2)
		data->game.player.player_pos_x += PLAYER_WIDTH;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->game.player_texture, data->game.player.player_pos_x,
		data->game.player.player_pos_y);
	return (0);
}

/*
 * Check if arguments are valid
 * Start reading the map if they are
 *	* Create a string that will finally contain the full map
 *	* Create a variable that will hold how many columns there are
 *	* Append each line to the string
 * Check if full map is valid
 *	* Is rectangular? (strlen(full_map) % columns == 0)
 *	* Are borders correct (1 everywhere in the corners)
 *	* Contains only one P and E
 *	* Contains at least one C
 *	* E is not blocked
 * Create the appropriately sized window
 * Start rendering the map
 *	* Iterate over each character and draw the appropriate texture
 */

/*
 * Keypress Event
 * Check if move is valid
 * Render player in new position if it is
 *	* Destroy old texture in that position and render player there
 *	* Destroy player texture from old pos and render empty there
 * Return and do nothing if it isn't
 */

int	main(int argc, char *argv[])
{
	char	*map_full;
	int		is_map_valid;
	t_data	data;
	int		*map_height_ptr;
	int		*map_width_ptr;
	int		map_height;
	int		map_width;
	int		*player_height_ptr;
	int		*player_width_ptr;
	int		player_height;
	int		player_width;

	map_height_ptr = &map_height;
	map_width_ptr = &map_width;
	player_height = PLAYER_HEIGHT;
	player_width = PLAYER_WIDTH;
	player_height_ptr = &player_height;
	player_width_ptr = &player_width;
	if (argc != 2)
		return (ft_putstr("Error\nPlease enter the map you would like to use\n"),
			1);
	if (!check_ext(argv[1]))
		return (ft_putstr("Error\nPlease input a map with a .ber file format\n"),
			1);
	map_full = read_map(open(argv[1], O_RDONLY));
	if (map_full == NULL)
		return (ft_putstr("Something went wrong while cooking"), 1);
	is_map_valid = check_map(map_full);
	if (is_map_valid)
		return (ft_putstr("Your map is not valid"), 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	get_map_size(map_full, map_height_ptr, map_width_ptr);
	map_height *= PLAYER_HEIGHT;
	map_width *= PLAYER_WIDTH;
	data.win_ptr = mlx_new_window(data.mlx_ptr, map_height, map_width,
		"so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	data.game.player_texture = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Player.xpm", player_width_ptr, player_height_ptr);
	data.game.wall_texture = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Border.xpm", player_width_ptr, player_height_ptr);
	data.game.collectable_texture = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Tablet.xpm", player_width_ptr, player_height_ptr);
	data.game.empty_texture = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Empty.xpm", player_width_ptr, player_height_ptr);
	data.game.exit_texture = mlx_xpm_file_to_image(data.mlx_ptr,
		"textures/Spaceship.xpm", player_width_ptr, player_height_ptr);
	data.game.player.player_pos_x = 0;
	data.game.player.player_pos_y = 0;
	render_map(map_full, &data);
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 17, handle_keypress, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
