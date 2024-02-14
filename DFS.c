#include "so_long.h"
#include <stdbool.h>
#include <stdio.h>

bool    check_path(char **map, char **visited, int x, int y)
{
    printf("%d, %d: %c\n", x, y, map[y][x]);
    if (map[y][x] == EXIT)
        return (true);
    if (map[y - 1][x] != WALL && visited[y - 1][x] != WALL)
    {
        puts("Up");
        visited[y - 1][x] = WALL;
        if (check_path(map, visited, x, y - 1))
            return (true);
    }
    if (map[y][x + 1] != WALL && visited[y][x + 1] != WALL)
    {
        puts("Right");
        visited[y][x + 1] = WALL;
        if (check_path(map,visited, x + 1, y))
            return (true);
    }
    if (map[y + 1][x] != WALL && visited[y + 1][x] != WALL)
    {
        puts("Down");
        visited[y + 1][x] = WALL;
        if (check_path(map, visited,x, y + 1))
            return (true);
    }
    if (map[y][x - 1] != WALL && visited[y][x - 1] != WALL)
        return (puts("Left"), visited[y][x - 1] = WALL, check_path(map,visited, x - 1, y));
    printf("Walls hit from everywhere. Stopping.\n");
    return (false);
}

static int	get_tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * @brief Duplicate an array of strings
 * 
 * @param tab The array containing the strings to be duplicated
 * @return char** A new malloced double pointer which is a duplicate of tab
 */
char	**ft_strdup_tab(char **tab)
{
	int		i;
	char	**dup_tab;

	i = -1;
	dup_tab = malloc(get_tab_size(tab) + 1);
	while (tab[++i])
		dup_tab[i] = ft_strdup(tab[i]);
	dup_tab[i] = NULL;
	return (dup_tab);
}

/**
 * @brief Creates a 2d array of size row and col.
 * Initializes it with NULL characters
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
	int	i;
	int	j;

	i = 0;
	string = NULL;
	dup_arr = NULL;
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
	dup_arr[i] = '\0';
	return (dup_arr);
}

void	get_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->game.map.rows)
	{
		j = 0;
		while (j < data->game.map.columns)
		{
			if (data->game.map.full[i][j] == 'P')
			{
				data->game.player.x = j;
				data->game.player.y = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (1);
	data.game.map.fd = open(argv[1], O_RDONLY);
	read_map(&data);
	char **visited = ft_make_2d_arr(data.game.map.columns, data.game.map.rows, '0');
    get_player_pos(&data);
    if (check_path(data.game.map.full, visited, data.game.player.x, data.game.player.y))
        printf("You have reached the exit\nThere is indeed a valid path.\n");
    else
        printf("All paths checked. No path to exit found\n");
    for (int i = 0; i < data.game.map.rows; i++)
    {
        for (int j = 0; j < data.game.map.columns; j++)
        {
            printf("%c ", visited[i][j]);
        }
        printf("\n");
    }
    return (0);
}
