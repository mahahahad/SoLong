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

int	get_exit_coordinates(t_data *data, int *x, int *y)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->game.map.full[j])
	{
		i = 0;
		while (data->game.map.full[j][i])
		{
			if (data->game.map.full[j][i] == EXIT)
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

int	display_enemy(t_data *data)
{
	int	x;
	int	y;

	x = data->game.alien.path->current_tile.x;
	y = data->game.alien.path->current_tile.y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.alien->texture, (x + 1) * PLAYER_WIDTH, (y + 1) * PLAYER_HEIGHT);
	return (0);
}

int	render_map(t_data *data)
{
	int	x;
	int	y;
	int	offset_x;
	int	offset_y;

	x = 0;
	y = 0;
	offset_x = 64;
	offset_y = 64;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	while (y < data->game.map.rows)
	{
		while (x < data->game.map.columns)
		{
			// ft_putstr("Printing a row\n");
			if (data->game.map.full[y][x] == WALL)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
				if (y > 0)
				{
					if (y == data->game.map.rows - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
					else if (x == 0)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->next->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
					else if (x == data->game.map.columns - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
					else
					{

						if ((x % 2) == 0)
							mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.asteroid_2->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
						else
							mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.asteroid_1->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
					}
				}
				if ((x == 0 && y == 0) || \
					(x == data->game.map.columns - 1 && y == data->game.map.rows - 1) || \
					(x == 0 && y == data->game.map.rows - 1) || \
					(x == data->game.map.columns - 1 && y == 0))
					mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->game.textures.border->next->next->next->next->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game.map.full[y][x] == EMPTY)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.empty->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
			if (data->game.map.full[y][x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.collectible->texture, x * PLAYER_WIDTH + offset_x, y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game.map.full[y][x] == PLAYER)
			{
				data->game.player.x = x;
				data->game.player.y = y;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.player->texture, x * PLAYER_WIDTH + offset_x, y
					* PLAYER_HEIGHT + offset_y);
			}
			if (data->game.map.full[y][x] == EXIT)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->game.textures.exit->texture, x * PLAYER_WIDTH + offset_x, y
					* PLAYER_HEIGHT + offset_y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (data->game.alien.path)
		display_enemy(data);
	char	*str = ft_strjoin("Moves: ", ft_itoa(data->game.moves));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 32, 0xFFFFFF, str);
	mlx_do_sync(data->mlx_ptr);
	free(str);
	return (0);
}

int	update_map(t_data *data)
{
	static int	frame;
	int	time_val;

	if (!frame)
		frame = clock();
	time_val = clock();
	if (time_val - frame > 50000)
	{
		data->game.textures.alien = data->game.textures.alien->next;
		data->game.textures.collectible = data->game.textures.collectible->next;
		data->game.textures.asteroid_1 = data->game.textures.asteroid_1->next;
		data->game.textures.asteroid_2 = data->game.textures.asteroid_2->next;
		data->game.textures.player = data->game.textures.player->next;
		frame = time_val;
	}
	render_map(data);
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
	else if (data->game.alien.path && \
	new_y == data->game.alien.path->current_tile.y && \
	new_x == data->game.alien.path->current_tile.x)
		return (ft_putstr("You died bruh\n"), handle_destroy(data), 0);
	data->game.map.full[data->game.player.y][data->game.player.x] = '0';
	data->game.player.x = new_x;
	data->game.player.y = new_y;
	data->game.map.full[new_y][new_x] = 'P';
	data->game.moves++;
	// render_map(data);
	ft_putstr("You have made ");
	ft_putnbr(data->game.moves);
	ft_putstr(" moves so far\n");
	// if (data.game.map.full[new_y][new_x] == '0')
	// 	return (data.game.map.full[new_y][new_x] = 'P', render_map(data), 0);
	return (0);
}	

void	move_enemy(t_data *data)
{
	static bool	backwards;
	
	if (!data->game.alien.path->prev_tile)
		backwards = false;
	if (!data->game.alien.path->next_tile)
		backwards = true;
	if (backwards)
		data->game.alien.path = data->game.alien.path->prev_tile;
	else
		data->game.alien.path = data->game.alien.path->next_tile;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC || keysym == KEY_Q)
		return (handle_destroy(data), 0);
	else
	{
		if (data->game.alien.path)
			move_enemy(data);
		if (keysym == KEY_W || keysym == KEY_ARROW_UP)
			move_to(data, data->game.player.x, data->game.player.y - 1);
		else if (keysym == KEY_A || keysym == KEY_ARROW_LEFT)
			move_to(data, data->game.player.x - 1, data->game.player.y);
		else if (keysym == KEY_S || keysym == KEY_ARROW_DOWN)
			move_to(data, data->game.player.x, data->game.player.y + 1);
		else if (keysym == KEY_D || keysym == KEY_ARROW_RIGHT)
			move_to(data, data->game.player.x + 1, data->game.player.y);
		else
			return (1);
	}
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
int	get_free_space(t_data *data, int x, int y, t_tile free_space[], int *size)
{
	int	dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int	dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int	free_tiles_found;
	int	i;
	int	new_y;
	int	new_x;
	int	j;
	t_tile	free_tile;
	
	i = 0;
	j = 0;
	free_tiles_found = 0;
	while (i < 8)
	{
		new_y = y + dy[i];
		new_x = x + dx[i];
		if (data->game.map.full[new_y][new_x] == EMPTY)
		{
			free_tile.x = new_x;
			free_tile.y = new_y;
			free_space[j++] = free_tile;
			free_tiles_found++;
		}
		else if (free_tiles_found)
			break ;
		i++;
	}
	*size = free_tiles_found;
	if (free_tiles_found < 2)
		return (1);
	return (0);
}

/**
 * @brief Assign all of the tiles in the tiles array to the path structure.
 * 
 * @param path The final path structure
 * @param tiles The tiles to be assigned to the path
 * @param tiles_size The size of the tiles array
 * @return int The status code of the assignment. 0 if successful, 1 otherwise.
 */
int	populate_path(t_path *path, t_tile tiles[], int size)
{
	int	i;
	// t_path *temp;

	i = 0;
	// path = (t_path *)malloc(sizeof(t_path *));
	path->prev_tile = NULL;
	path->next_tile = NULL;
	while (i < size)
	{
		path->current_tile = tiles[i];
		path->next_tile = (t_path *)malloc(sizeof(t_path *));
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
	t_tile	free_space_tiles[8];
	int		size;
	// t_tile	empty;

	// empty.x = 0;
	// empty.y = 0;
	path = (t_path *)malloc(sizeof(t_path *));
	// path = NULL;
	if (get_exit_coordinates(data, &exit_x, &exit_y) != 0)
		return (NULL);
	if (get_free_space(data, exit_x, exit_y, free_space_tiles, &size) != 0)
		return (NULL);
	populate_path(path, free_space_tiles, size);
	return (path);
}

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
	int	screen_x;
	int	screen_y;
	mlx_get_screen_size(data.mlx_ptr, &screen_x, &screen_y);
	data.win_ptr = mlx_new_window(data.mlx_ptr, (data.game.map.columns + 2) * PLAYER_WIDTH, (data.game.map.rows + 2) * PLAYER_HEIGHT, "so_long");
	if (!data.win_ptr)
		return (free(data.mlx_ptr), 1);
	// Initalize Texture pointers
	data.game.textures.player = init_animated_sprite(data, "textures/Player/Player");
	data.game.textures.collectible = init_animated_sprite(data, "textures/Collectible/Collectible");
	data.game.textures.wall = init_animated_sprite(data, "textures/Wall/SpaceRocks");
	data.game.textures.exit = init_animated_sprite(data, "textures/Exit");
	data.game.textures.empty = init_animated_sprite(data, "textures/Empty");
	data.game.textures.border = init_animated_sprite(data, "textures/Border");
	data.game.textures.asteroid_1 = init_animated_sprite(data, "textures/Asteroid1/Asteroid1");
	data.game.textures.asteroid_2 = init_animated_sprite(data, "textures/Asteroid2/Asteroid2");
	data.game.textures.alien = init_animated_sprite(data, "textures/Alien/Alien");
	data.game.moves = 0;
	data.game.alien.path = initialize_enemy_path(&data);
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
