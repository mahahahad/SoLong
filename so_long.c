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

void	print_arr(char **arr, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

/// @brief Read the map the file descriptor is pointing to and return it when finished
/// @param fd
// The file descriptor that points to the map to read
/// @return
// The complete map as a string, seperated by newlines
char	*read_map(t_data *data)
{
	char	*map_full;
	char	*str;
	int		fd;

	str = NULL;
	map_full = NULL;
	fd = data->game.map.fd;
	data->game.map.rows = 0;
	data->game.map.columns = 0;
	str = get_next_line(fd);
	map_full = malloc(1);
	// TODO: LEAKS
	map_full = ft_strjoin(map_full, str);
	while (str != NULL)
	{
		str = get_next_line(fd);
		data->game.map.rows++;
		if (str == NULL)
			break ;
		// TODO: LEAKS
		map_full = ft_strjoin(map_full, str);
	}
	data->game.map.full = ft_split(map_full, '\n');
	data->game.map.columns = ft_strlen(data->game.map.full[0]);
	print_arr(data->game.map.full, data->game.map.rows, data->game.map.columns);
	return (close(fd), map_full);
}

/// @brief Count the number of columns in the provided map
/// @param map The map to count
/// @return The number of columns INCLUDING THE NEWLINE CHARACTER
// static int	count_columns(char *map)
// {
// 	int	columns;

// 	columns = 0;
// 	while (map[columns] != '\n')
// 		columns++;
// 	return (++columns);
// }

/// @brief Gets the width and height of the provided map
/// @param map The map to measure
/// @param height The variable that will contain the height
/// @param width The variable that will contain the width
// void	get_map_size(t_data *data)
// {
// 	int	columns;
// 	int	rows;

// 	columns = 0;
// 	rows = 0;
// 	while (data->game.map.full[columns] != '\n')
// 		columns++;
// 	while (map[rows] != '\0')
// 		rows += columns + 1;
// 	data->game.map.height = columns;
// 	data->game.map.width = rows / columns;
// }

/// @brief Check if the provided map is valid or not
/// @param map
// 	The complete map provided as a string
/// @return
// Boolean if map is valid (0) or invalid (1)
int	check_map(t_data *data)
{
	int	is_valid;

	(void)data;
	is_valid = 1;
	// map_width = count_columns(map);
	// if (ft_strlen(map) % map_width == 0)
	// 	is_valid = 0;
	// else
	// 	is_valid = 1;
	return (is_valid);
}

void	render_map(t_data *data)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	x = 0;
	y = 0;
	while (y < data->game.map.rows)
	{
		while (x < data->game.map.columns)
		{
			// ft_putstr("Printing a row\n");
			if (data->game.map.full[y][x] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.wall_texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			if (data->game.map.full[y][x] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.empty_texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			if (data->game.map.full[y][x] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.collectable_texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			if (data->game.map.full[y][x] == 'P')
			{
				data->game.player.x = x;
				data->game.player.y = y;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.player_texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			}
			if (data->game.map.full[y][x] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.exit_texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			x++;
		}
		// ft_putstr("Done with a row\n");
		y++;
		x = 0;
	}
}

/*
111111
10P001
1000E1
111111

[[1,1,1,1,1,1],
[1,0,P,0,0,1],
[1,0,0,0,E,1],
[1,1,1,1,1,1]]
*/
/// @brief Checks if a move is valid based on the key code provided
/// @param keycode The move to check is valid
/// @param data The data structure holding all the information related to the game including the map
/// @return 0 or 1 if it is valid or invalid respectively.
// int	is_move_valid(int keycode, t_data *data)
// {
// 	if (keycode == KEY_W)
// 	{
// 		if (data->game.map.full[data->game.player.index - (data->game.map.width
// 				/ PLAYER_WIDTH) + 1] == '1')
// 			return (1);
// 	}
// 	return (0);
// }

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

// TODO: FIX THIS
int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC)
		return (handle_destroy(data), 0);
	// ft_putstr(data->game.map.full);
	// ft_putstr("\n");
	// data->game.map.full[data->game.player.index] = '0';
	// if (keysym == KEY_W)
	// {
	// 	data->game.player.index -= (data->game.map.width / PLAYER_WIDTH);
	// }
	// if (keysym == KEY_A)
	// {
	// 	data->game.player.index -= 1;
	// }
	// if (keysym == KEY_S)
	// {
	// 	data->game.player.index += data->game.map.height / PLAYER_HEIGHT;
	// }
	// if (keysym == KEY_D)
	// {
	// 	data->game.player.index += 1;
	// }
	// data->game.map.full[data->game.player.index] = 'P';
	// render_map(data);
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
	int		*player_height_ptr;
	int		*player_width_ptr;
	int		player_height;
	int		player_width;

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
	data.game.map.fd = open(argv[1], O_RDONLY);
	map_full = read_map(&data);
	if (map_full == NULL)
		return (ft_putstr("Something went wrong while cooking. Your map couldn't be opened\n"),
				1);
	is_map_valid = check_map(&data);
	if (!is_map_valid)
		return (ft_putstr("Your map is not valid"), 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.game.map.columns
		* PLAYER_WIDTH, data.game.map.rows * PLAYER_HEIGHT, "so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	// Initalize Texture pointers
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
	render_map(&data);
	// Handle keypress and close window events
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	mlx_hook(data.win_ptr, 2, 1L << 17, handle_keypress, &data);
	// Loop infinitely to avoid closing window until specified by user
	mlx_loop(data.mlx_ptr);
	return (0);
}
