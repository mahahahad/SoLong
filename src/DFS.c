/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:39:36 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/04 21:53:14 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * @brief Creates a 2d array of size row and col.
 * Initializes it with fill_char
 *
 * @param col
 * @param row
 * @param fill_char
 * @return char**
 */
char	**ft_make_2d_arr(int col, int row, char fill_char)
{
	char	**dup_arr;
	char	*string;
	int		i;
	int		j;

	i = 0;
	string = NULL;
	dup_arr = malloc((row + 1) * sizeof(char *));
	while (i < row)
	{
		string = malloc(col + 1);
		j = 0;
		while (j < col)
		{
			string[j] = fill_char;
			j++;
		}
		string[j] = '\0';
		dup_arr[i] = string;
		i++;
	}
	dup_arr[i] = NULL;
	return (dup_arr);
}

/**
 * @brief Frees each string inside the 2d array provided to the function,
 * followed by freeing the entire array itself
 *
 * @param arr
 */
void	ft_free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	get_player_pos(char **map, int *x, int *y)
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
				*x = j;
				*y = i;
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
bool	check_path(char **map)
{
	char	**visited;
	int		player_x;
	int		player_y;
	bool	res;

	player_x = 0;
	player_y = 0;
	visited = ft_make_2d_arr(ft_strlen(map[0]), get_tab_size(map), '0');
	get_player_pos(map, &player_x, &player_y);
	res = check_tile(map, visited, player_x, player_y);
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
