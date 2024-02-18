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

static bool	is_ext_valid(char *file)
{
	int		i;

	i = strlen(file) - 4;
	if (i <= 0)
		return (false);
	while (i--)
		file++;
	if (ft_strcmp(file, ".ber") == 0)
		return (true);
	return (false);
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
// 	while (data.game.map.full[columns] != '\n')
// 		columns++;
// 	while (map[rows] != '\0')
// 		rows += columns + 1;
// 	data.game.map.height = columns;
// 	data.game.map.width = rows / columns;
// }

/// @brief Check if the provided map is valid or not
/// @param data
// 	The data structure containing all the relevant game variables
/// @return
// 	Boolean if map is valid (0) or invalid (1)
int	check_map(t_data *data)
{

	int 	y;
	int 	x;
	int	exit_count;
	int	player_count;

	y = 0;
	exit_count = 0;
	player_count = 0;
	while (y < data->game.map.rows)
	{
		x = 0;
		if (data->game.map.full[y][0] != '1' || data->game.map.full[y][data->game.map.columns-1] != '1')
			return (ft_putstr("Error\nMap must be surrounded by walls\n"), exit(1), 1);
		while (x < data->game.map.columns)
		{
			if ((y == 0 || y == data->game.map.rows - 1) && data->game.map.full[y][x] != '1')
				return (ft_putstr("Error\nMap must be surrounded by walls\n"), exit(1), 1);
			else if (data->game.map.full[y][x] == 'C')
				data->game.collectables.total++;
			else if (data->game.map.full[y][x] == 'E')
				exit_count++;
			else if (data->game.map.full[y][x] == 'P')
				player_count++;
			else if (data->game.map.full[y][x] != '0' && data->game.map.full[y][x] != '1')
				return (ft_putstr("Error\nInvalid character detected in map\n"), write(1, &data->game.map.full[y][x], 1), exit(1), 1);

			x++;
		}
		y++;
	}
	if (data->game.collectables.total == 0)
		return (ft_putstr("Error\nPlease have at least one collectable in the map\n"), exit(1), 1);
	if (exit_count != 1)
		return (ft_putstr("Error\nOnly one exit must be present in the map\n"), exit(1), 1);
	if (player_count != 1)
		return (ft_putstr("Error\nOnly one player must be present in the map\n"), exit(1), 1);
	// map_width = count_columns(map);
	// if (ft_strlen(map) % map_width == 0)
	// 	is_valid = 0;
	// else
	// 	is_valid = 1;
	return (0);
}

int	render_map(t_data *data)
{
	int	x;
	int	y;
	static bool	walls_rendered;

	x = 0;
	y = 0;
	while (y < data->game.map.rows)
	{
		while (x < data->game.map.columns)
		{
			// ft_putstr("Printing a row\n");
			if (data->game.map.full[y][x] == WALL && !walls_rendered)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
				if (y > 0)
				{
					if (y == data->game.map.rows - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
					else if (x == 0)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->next->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
					else if (x == data->game.map.columns - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
					else
					{

						if ((rand() % 10) <= 5)
							data->game.textures.wall = data->game.textures.wall->next;
						else if ((rand() % 3) <= 1)
							data->game.textures.wall = data->game.textures.wall->next->next;
						else
							data->game.textures.wall = data->game.textures.wall->next->next;
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.wall->next->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
					}
				}
				if ((x == 0 && y == 0) || \
					(x == data->game.map.columns - 1 && y == data->game.map.rows - 1) || \
					(x == 0 && y == data->game.map.rows - 1) || \
					(x == data->game.map.columns - 1 && y == 0))
					mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->next->next->texture, x * PLAYER_WIDTH, y  * PLAYER_HEIGHT);
			}
			if (data->game.map.full[y][x] == EMPTY)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.empty->texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			if (data->game.map.full[y][x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.collectible->texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			}
			if (data->game.map.full[y][x] == PLAYER)
			{
				data->game.player.x = x;
				data->game.player.y = y;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.player->texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			}
			if (data->game.map.full[y][x] == EXIT)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.exit->texture, x * PLAYER_WIDTH, y
					* PLAYER_HEIGHT);
			x++;
		}
		y++;
		x = 0;
	}
	walls_rendered = true;
	// usleep(166667);
	// data->game.textures.player = data->game.textures.player->next;
	// data->game.textures.collectible = data->game.textures.collectible->next;
	return (0);
}

int	update_map(t_data *data)
{
	static int	frame;
	if ((frame % 1667) == 0)
	{
		data->game.textures.collectible = data->game.textures.collectible->next;
		data->game.textures.player = data->game.textures.player->next;
	}
	// else
		// frame = 0;
	render_map(data);
	frame++;
	return (0);
}

/// @brief Checks if a move is valid based on the key code provided
/// @param keycode The move to check is valid
/// @param data The data structure holding all the information related to the game including the map
/// @return 0 or 1 if it is valid or invalid respectively.
// int	is_move_valid(int keycode, t_data *data)
// {
// 	if (keycode == KEY_W)
// 	{
// 		if (data.game.map.full[data.game.player.index - (data.game.map.width
// 				/ PLAYER_WIDTH) + 1] == '1')
// 			return (1);
// 	}
// 	return (0);
// }

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data->game.map.full);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	move_to(t_data *data, int new_x, int new_y)
{
	// write(1, &data.game.map.full[new_y][new_x], 1);
	// write(1, "\n", 1);
	if (data->game.map.full[new_y][new_x] == '1')
		return (1);
	else if (data->game.map.full[new_y][new_x] == 'C')
		++data->game.collectables.collected;
	else if (data->game.map.full[new_y][new_x] == 'E')
	{
		if (data->game.collectables.collected == data->game.collectables.total)
			return (ft_putstr("W's in the shaaaat!!!\n"), handle_destroy(data), 0);
		else
			return (1);
	}
	data->game.map.full[data->game.player.y][data->game.player.x] = '0';
	data->game.player.x = new_x;
	data->game.player.y = new_y;
	data->game.map.full[new_y][new_x] = 'P';
	data->game.moves++;
	// render_map(data);
	char	*str = ft_strjoin("Moves: ", ft_itoa(data->game.moves));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 24, 24, 16, str);
	free(str);
	ft_putstr("You have made ");
	ft_putnbr(data->game.moves);
	ft_putstr(" moves so far\n");
	// if (data.game.map.full[new_y][new_x] == '0')
	// 	return (data.game.map.full[new_y][new_x] = 'P', render_map(data), 0);
	return (0);
}	

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC || keysym == KEY_Q)
		return (handle_destroy(data), 0);
	else if (keysym == KEY_W || keysym == KEY_ARROW_UP)
		move_to(data, data->game.player.x, data->game.player.y - 1);
	else if (keysym == KEY_A || keysym == KEY_ARROW_LEFT)
		move_to(data, data->game.player.x - 1, data->game.player.y);
	else if (keysym == KEY_S || keysym == KEY_ARROW_DOWN)
		move_to(data, data->game.player.x, data->game.player.y + 1);
	else if (keysym == KEY_D || keysym == KEY_ARROW_RIGHT)
		move_to(data, data->game.player.x + 1, data->game.player.y);
	else
		return (1);
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
 *	* Render empty in player old position
 * Return and do nothing if it isn't
 */

int	main(int argc, char *argv[])
{
	char		*map_full;
	int		is_map_invalid;
	t_data		data;
	// int		*player_height_ptr;
	// int		*player_width_ptr;
	// int		player_height;
	// int		player_width;

	// player_height = PLAYER_HEIGHT;
	// player_width = PLAYER_WIDTH;
	if (argc != 2)
		return (ft_putstr("Error\nPlease enter the map you would like to use\n"),
			1);
	if (!is_ext_valid(argv[1]))
		return (ft_putstr("Error\nPlease input a map with a .ber file format\n"),
			1);
	data.game.map.fd = open(argv[1], O_RDONLY);
	map_full = read_map(&data);
	if (map_full == NULL)
		return (ft_putstr("Something went wrong while cooking. Your map couldn't be opened\n"),
				1);
	free(map_full);
	// Initialize collectables
	data.game.collectables.total = 0;
	data.game.collectables.collected = 0;
	is_map_invalid = check_map(&data);
	if (is_map_invalid)
		return (ft_putstr("Your map is not valid"), 1);
	is_map_invalid = check_path(data.game.map.full);
	if (!is_map_invalid)
		return (ft_putstr("There is no path to the exit"), 1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.game.map.columns
		* PLAYER_WIDTH, data.game.map.rows * PLAYER_HEIGHT - 1, "so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	// Initalize Texture pointers
	data.game.textures.player = init_animated_sprite(data, "textures/Player/Player");
	data.game.textures.collectible = init_animated_sprite(data, "textures/Collectible/Collectible");
	data.game.textures.wall = init_animated_sprite(data, "textures/Wall/SpaceRocks");
	data.game.textures.exit = init_animated_sprite(data, "textures/Exit");
	data.game.textures.empty = init_animated_sprite(data, "textures/Empty");
	data.game.textures.border = init_animated_sprite(data, "textures/Border");
	data.game.moves = 0;
	render_map(&data);
	// Handle keypress and close window events
	mlx_hook(data.win_ptr, 17, 1L << 2, handle_destroy, &data);
	// For Linux
	mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	mlx_loop_hook(data.mlx_ptr, update_map, &data);
	// mlx_key_hook(data.win_ptr, handle_keypress, &data);
	// Loop infinitely to avoid closing window until specified by user
	mlx_loop(data.mlx_ptr);
	return (0);
}
