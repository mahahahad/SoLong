/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long->c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:50:08 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/03 16:03:47 by maabdull         ###   ########.fr       */
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

/// @brief Check if the provided map is valid or not
/// @param data
// 	The data structure containing all the relevant game variables
/// @return
// 	Boolean if map is valid (0) or invalid (1)
int	check_map(t_data *data)
{
	int 	y;
	int 	x;
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
			data->game->map->full[y][data->game->map->columns-1] != '1')
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

int	display_enemy(t_data *data)
{
	int	x;
	int	y;

	if (!data->game->alien->path)
		return (1);
	x = data->game->alien->path->current_tile->x;
	y = data->game->alien->path->current_tile->y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
							data->game->textures->alien->texture,\
							(x + 1) * PLAYER_WIDTH,\
							(y + 1) * PLAYER_HEIGHT);
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
	while (y < data->game->map->rows)
	{
		while (x < data->game->map->columns)
		{
			// ft_putstr("Printing a row\n");
			if (data->game->map->full[y][x] == WALL)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->border->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
				if (y > 0)
				{
					if (y == data->game->map->rows - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
						data->game->textures->border->next->next->texture,\
						x * PLAYER_WIDTH + offset_x,\
						y * PLAYER_HEIGHT + offset_y);
					else if (x == 0)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
						data->game->textures->border->next->next->next->texture,\
						x * PLAYER_WIDTH + offset_x,\
						y * PLAYER_HEIGHT + offset_y);
					else if (x == data->game->map->columns - 1)
						mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
						data->game->textures->border->next->texture,\
						x * PLAYER_WIDTH + offset_x,\
						y * PLAYER_HEIGHT + offset_y);
					else
					{
						if ((x % 2) == 0)
							mlx_put_image_to_window(data->mlx_ptr,\
							data->win_ptr,\
							data->game->textures->asteroid_2->texture,\
							x * PLAYER_WIDTH + offset_x,\
							y * PLAYER_HEIGHT + offset_y);
						else
							mlx_put_image_to_window(data->mlx_ptr,\
							data->win_ptr,\
							data->game->textures->asteroid_1->texture,\
							x * PLAYER_WIDTH + offset_x,\
							y * PLAYER_HEIGHT + offset_y);
					}
				}
				if ((x == 0 && y == 0) || \
					(x == data->game->map->columns - 1 && \
					 y == data->game->map->rows - 1) || \
					(x == 0 && y == data->game->map->rows - 1) || \
					(x == data->game->map->columns - 1 && y == 0))
					mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->border->next->next->next->next->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == EMPTY)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->empty->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
			if (data->game->map->full[y][x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->collectible->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == PLAYER)
			{
				data->game->player->x = x;
				data->game->player->y = y;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->player->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
			}
			if (data->game->map->full[y][x] == EXIT)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,\
				data->game->textures->exit->texture,\
				x * PLAYER_WIDTH + offset_x,\
				y * PLAYER_HEIGHT + offset_y);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (data->game->alien)
		display_enemy(data);
	char	*str = ft_strjoin("Moves: ", ft_itoa(data->game->moves));
	mlx_string_put(data->mlx_ptr, data->win_ptr, 32, 32, 0xFFFFFF, str);
	mlx_do_sync(data->mlx_ptr);
	free(str);
	return (0);
}

int	update_map(t_data *data)
{
	static int	frame;
	int			time_val;

	if (!frame)
		frame = clock();
	time_val = clock();
	if (time_val - frame > 50000)
	{
		data->game->textures->alien = data->game->textures->alien->next;
		data->game->textures->collectible = data->game->textures->collectible->next;
		data->game->textures->asteroid_1 = data->game->textures->asteroid_1->next;
		data->game->textures->asteroid_2 = data->game->textures->asteroid_2->next;
		data->game->textures->player = data->game->textures->player->next;
		frame = time_val;
	}
	render_map(data);
	return (0);
}

void	free_alien_path(t_data *data)
{
	while (data->game->alien->path->next_tile)
	{
		free(data->game->alien->path->current_tile);
		free(data->game->alien->path->prev_tile);
		data->game->alien->path = data->game->alien->path->next_tile;
	}
	// free(data->game->alien->path);
}

void	free_sprite(t_sprite_animated *sprite)
{
	t_sprite_animated	*temp;
	t_sprite_animated	*first;

	first = sprite;
	// free(sprite);
	while (sprite->texture != first->texture)
	{
		temp = sprite->next;
		free(sprite);
		sprite = temp;
	}
}

void	free_textures(t_data *data)
{
	free_sprite(data->game->textures->alien);
	free_sprite(data->game->textures->asteroid_1);
	free_sprite(data->game->textures->asteroid_2);
	free_sprite(data->game->textures->border);
	free_sprite(data->game->textures->collectible);
	free_sprite(data->game->textures->empty);
	free_sprite(data->game->textures->exit);
	free_sprite(data->game->textures->player);
	free_sprite(data->game->textures->wall);
	free(data->game->textures);
}

void	free_data_struct(t_data *data)
{
	free(data->game->collectables);
	free(data->game->map->full);
	free(data->game->map);
	free(data->game->player);
	free_textures(data);
	if (data->game->alien)
	{
		free_alien_path(data);
		free(data->game->alien);
	}
	free(data->mlx_ptr);
}

int	handle_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free_data_struct(data);
	exit(0);
	return (0);
}

int	move_to(t_data *data, int new_x, int new_y)
{
	if (data->game->map->full[new_y][new_x] == '1')
		return (1);
	else if (data->game->map->full[new_y][new_x] == 'C')
		++data->game->collectables->collected;
	else if (data->game->map->full[new_y][new_x] == 'E')
	{
		if (data->game->collectables->collected == data->game->collectables->total)
		{
			ft_putstr("W's in the shaaaat!!!\n");
			handle_destroy(data);
			return (0);
		}
		else
			return (1);
	}
	else if (data->game->alien && \
	new_y == data->game->alien->path->current_tile->y && \
	new_x == data->game->alien->path->current_tile->x)
	{
		ft_putstr("You died bruh\n");
		handle_destroy(data);
		return (0);
	}
	data->game->map->full[data->game->player->y][data->game->player->x] = '0';
	data->game->player->x = new_x;
	data->game->player->y = new_y;
	data->game->map->full[new_y][new_x] = 'P';
	data->game->moves++;
	ft_putstr("You have made ");
	ft_putnbr(data->game->moves);
	ft_putstr(" moves so far\n");
	return (0);
}	

void	move_enemy(t_data *data)
{
	static bool	backwards;
	
	if (!data->game->alien)
		return ;
	if (!data->game->alien->path->prev_tile)
		backwards = false;
	if (!data->game->alien->path->next_tile)
		backwards = true;
	if (backwards)
		data->game->alien->path = data->game->alien->path->prev_tile;
	else
		data->game->alien->path = data->game->alien->path->next_tile;
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == KEY_ESC || keysym == KEY_Q)
		return (handle_destroy(data), 0);
	else
	{
		if (data->game->alien)
			move_enemy(data);
		if (keysym == KEY_W || keysym == KEY_ARROW_UP)
			move_to(data, data->game->player->x, data->game->player->y - 1);
		else if (keysym == KEY_A || keysym == KEY_ARROW_LEFT)
			move_to(data, data->game->player->x - 1, data->game->player->y);
		else if (keysym == KEY_S || keysym == KEY_ARROW_DOWN)
			move_to(data, data->game->player->x, data->game->player->y + 1);
		else if (keysym == KEY_D || keysym == KEY_ARROW_RIGHT)
			move_to(data, data->game->player->x + 1, data->game->player->y);
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
 * @brief Gets the free space around the specified coordinates->
 * If atleast 2 tiles on one side are empty tiles, they are considered
 * free space-> Goes in the order Top->Right->Bottom->Left
 * 
 * @param data The data structure containing all the game variables
 * @param x The x coordinate of the anchor
 * @param y The y coordinate of the anchor
 * @param free_space[] The free tiles surrounding the object
 * @param size The number of free tiles surround the object
 * @return int The status code, 0 if atleast 2 empty spaces were found,
 * 1 otherwise
 */
int	get_free_space(t_data *data, int x, int y, t_tile *free_space[], int *size)
{
	int	dx[] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int	dy[] = {-1, -1, -1, 0, 1, 1, 1, 0};
	int	free_tiles_found;
	int	i;
	int	new_y;
	int	new_x;
	t_tile	*free_tile;
	
	i = 0;
	free_tiles_found = 0;
	free_tile = NULL;
	while (i < 8)
	{
		new_y = y + dy[i];
		new_x = x + dx[i];
		if (data->game->map->full[new_y][new_x] == EMPTY)
		{
			free_tile = malloc(sizeof(t_tile));
			if (!free_tile)
				return (ft_error("Could not allocate space"));
			free_tile->x = new_x;
			free_tile->y = new_y;
			free_space[free_tiles_found] = free_tile;
			free_tiles_found++;
		}
		else
		{
			if (free_tiles_found >= 2)
				break ;
			else
			{
				free_tiles_found = 0;
			}
		}
		i++;
	}
	*size = free_tiles_found;
	if (free_tiles_found < 2)
		return (1);
	return (0);
}

/**
 * @brief Assign all of the tiles in the tiles array to the path structure->
 * 
 * @param path The final path structure
 * @param tiles The tiles to be assigned to the path
 * @param tiles_size The size of the tiles array
 * @return int The status code of the assignment-> 0 if successful, 1 otherwise->
 */
int	populate_path(t_path *path, t_tile *tiles[], int size)
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
		path->next_tile = malloc(sizeof(t_path));
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
 * the exit-> Any side of the exit that has at least 2 empty spaces is
 * considered free space-> Uses the first free sides found as the path if all
 * sides are not empty->
 * 
 * @param data The data structure containing game variables
 * @return t_path The path of this enemy
 */
t_path	*initialize_enemy_path(t_data *data)
{
	int		exit_x;
	int		exit_y;
	t_path	*path;
	t_tile	*free_space_tiles[8];
	int		size;

	if (get_exit_coordinates(data, &exit_x, &exit_y) != 0)
		return (NULL);
	if (get_free_space(data, exit_x, exit_y, free_space_tiles, &size) != 0)
		return (NULL);
	path = malloc(sizeof(t_path));
	populate_path(path, free_space_tiles, size);
	data->game->alien = malloc(sizeof(t_alien));
	data->game->alien->path = path;
	return (path);
}

// Initalize Texture pointers
void	init_sprites(t_data *data)
{
	data->game->textures->player = init_animated_sprite(*data,\
	"textures/Player/Player");
	data->game->textures->collectible = init_animated_sprite(*data,\
	"textures/Collectible/Collectible");
	data->game->textures->wall = init_animated_sprite(*data,\
	"textures/Wall/SpaceRocks");
	data->game->textures->exit = init_animated_sprite(*data, "textures/Exit");
	data->game->textures->empty = init_animated_sprite(*data, "textures/Empty");
	data->game->textures->border = init_animated_sprite(*data, "textures/Border");
	data->game->textures->asteroid_1 = init_animated_sprite(*data,\
	"textures/Asteroid1/Asteroid1");
	data->game->textures->asteroid_2 = init_animated_sprite(*data,\
	"textures/Asteroid2/Asteroid2");
	data->game->textures->alien = init_animated_sprite(*data,\
	"textures/Alien/Alien");
}

int	init_data_struct(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_error("MLX could not be initialized"));
	data->game = malloc(sizeof(t_game));
	data->game->textures = malloc(sizeof(t_textures));
	data->game->collectables = malloc(sizeof(t_collectables));
	data->game->player = malloc(sizeof(t_player));
	data->game->map = malloc(sizeof(t_map));
	data->game->alien = NULL;
	if (!data->game || \
		!data->game->textures || \
		!data->game->collectables || \
		!data->game->player || \
		!data->game->map)
		return (ft_error("Could not allocate enough space"));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_error("Could not allocate enough space"));
	if (argc != 2)
		return (ft_error("Please enter the map you would like to use"));
	if (!is_ext_valid(argv[1]))
		return (ft_error("Please input a map with a .ber file format"));
	init_data_struct(data);
	data->game->map->fd = open(argv[1], O_RDONLY);
	if (read_map(data))
		return (ft_error("Your map couldn't be opened"));
	if (check_map(data))
		return (ft_putstr("Your map is not valid"), 1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,\
	(data->game->map->columns + 2) * PLAYER_WIDTH,\
	(data->game->map->rows + 2) * PLAYER_HEIGHT,\
	"so_long");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), ft_error("Window could not be created"));
	init_sprites(data);
	initialize_enemy_path(data);
	mlx_hook(data->win_ptr, 17, 1L << 2, handle_destroy, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, handle_keypress, data);
	mlx_loop_hook(data->mlx_ptr, update_map, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
