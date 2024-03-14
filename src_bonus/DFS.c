/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:39:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/07 10:12:13 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/**
 * @brief Get the size of a 2d arr. Relies on NULL Terminator
 *
 * @param tab The 2d arr who's size is to be found
 * @return int The size
 */
static int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	get_player_pos(t_data *data, char **map)
{
	int	i;
	int	j;
	int	rows;
	int	columns;

	i = 0;
	rows = get_tab_size(map);
	columns = ft_strlen(map[0]);
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (map[i][j] == 'P')
			{
				data->game->player->x = j;
				data->game->player->y = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

bool	check_tile(char **map, char **visited, int x, int y)
{
	if (map[y][x] == EXIT)
		return (true);
	if (map[y - 1][x] != WALL && visited[y - 1][x] != WALL)
	{
		visited[y - 1][x] = WALL;
		if (check_tile(map, visited, x, y - 1))
			return (true);
	}
	if (map[y][x + 1] != WALL && visited[y][x + 1] != WALL)
	{
		visited[y][x + 1] = WALL;
		if (check_tile(map, visited, x + 1, y))
			return (true);
	}
	if (map[y + 1][x] != WALL && visited[y + 1][x] != WALL)
	{
		visited[y + 1][x] = WALL;
		if (check_tile(map, visited, x, y + 1))
			return (true);
	}
	if (map[y][x - 1] != WALL && visited[y][x - 1] != WALL)
		return (visited[y][x - 1] = WALL, check_tile(map, visited, x - 1, y));
	return (false);
}

/**
 * @brief Checks whether there is a valid path from the players start position
 * to the exit. Uses recursion
 *
 * @param map The full map to be checked. Expected in double ptr format
 *
 * @return true if there is a valid path from start to finish.
 * @return false otherwise
 */
bool	check_path(t_data *data, char **map)
{
	char	**visited;
	bool	res;

	visited = ft_make_2d_arr(ft_strlen(map[0]), get_tab_size(map), '0');
	get_player_pos(data, map);
	if (!data->game->player->x)
		return (ft_free_2d_arr(visited), false);
	res = check_tile(map, visited, data->game->player->x,
			data->game->player->y);
	return (ft_free_2d_arr(visited), res);
}

// int main(int argc, char *argv[])
// {
// 	t_data	data;

// 	if (argc != 2)
// 		return (1);
// 	data.game.map.fd = open(argv[1], O_RDONLY);
// 	read_map(&data);
//     if (check_path(data.game.map.full))
//         printf("You have reached the exit\nThere is indeed a valid path.\n");
//     else
//         printf("All paths checked. No path to exit found\n");
//     return (0);
// }
