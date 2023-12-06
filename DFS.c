#include "so_long.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct s_map_path
{
	bool	valid_path;
	char	**map;
}			t_map_path;

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
/*
Check if a valid path is present from player to exit
Sets the path member of the map structure to true or valid or whatever
Check this member later on and display the relevant message and action
OR
pass in a visited array that contains a 1 or 0 in all the relevant positions AKA the same x and y
*/
int	check_path(t_map_path *map_struct, char **map, int y, int x, char **visited)
{
	printf("%d, %d: %c\n", y, x, map[y][x]);
	// print_arr(map, 5, 5);
	visited[y][x] = '1';
	print_arr(visited, 5, 5);
	if (map[y][x] == 'E')
		return (map_struct->valid_path = true, true);
	if (y < 0 || x < 0 || map[y][x] == '1')
		return (false);
	if (check_path(map_struct, map, y - 1, x, visited) && visited[y
		- 1][x] != '1')
		return (visited[y - 1][x] = '1', true);
	else if (check_path(map_struct, map, y, x + 1, visited) && visited[y][x
		+ 1] != '1')
		return (visited[y][x + 1] = '1', true);
	else if (check_path(map_struct, map, y + 1, x, visited) && visited[y
		+ 1][x] != '1')
		return (visited[y + 1][x] = '1', true);
	else if (check_path(map_struct, map, y, x - 1, visited) && visited[y][x
		- 1] != '1')
		return (visited[y][x - 1] = '1', true);
	return (false);
}

int	main(void)
{
	t_map_path	map;
	char		*map_full;
	char		**visited;

	map_full = "11111\n10E01\n100C1\n10P01\n11111\n";
	map.map = ft_split(map_full, '\n');
	visited = ft_split("00000\n00000\n00000\n00000\n00000\n", '\n');
	check_path(&map, map.map, 3, 2, visited);
	if (map.valid_path == true)
		printf("There is a valid path");
	else
		printf("Error\nThere is no valid path.\n");
	return (0);
}
