#include "so_long.h"
#include <stdbool.h>
#include <stdio.h>

bool    check_path(char **map, char visited[5][5], int x, int y)
{
    printf("%d, %d: %c\n", x, y, map[y][x]);
    if (map[y][x] == 'E')
        return (true);
    if (map[y - 1][x] != '1' && visited[y - 1][x] != '1')
    {
        puts("Up");
        visited[y - 1][x] = '1';
        if (check_path(map, visited, x, y - 1))
            return (true);
    }
    if (map[y][x + 1] != '1' && visited[y][x + 1] != '1')
    {
        puts("Right");
        visited[y][x + 1] = '1';
        if (check_path(map,visited, x + 1, y))
            return (true);
    }
    if (map[y + 1][x] != '1' && visited[y + 1][x] != '1')
    {
        puts("Down");
        visited[y + 1][x] = '1';
        if (check_path(map, visited,x, y + 1))
            return (true);
    }
    if (map[y][x - 1] != '1' && visited[y][x - 1] != '1')
        return (puts("Left"), visited[y][x - 1] = '1', check_path(map,visited, x - 1, y));
    printf("Walls hit from everywhere. Stopping.\n");
    return (false);
}

int main() {
    char *map[5] = {
        "11111",
        "10E11",
        "10101",
        "10P01",
        "11111"
    };
    char visited[][5] = {
        "00000",
        "00000",
        "00000",
        "00000",
        "00000"
    };
    
    if (check_path(map, visited, 2, 3))
        printf("You have reached the exit\nThere is indeed a valid path.\n");
    else
        printf("All paths checked. No path to exit found\n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", visited[i][j]);
        }
        printf("\n");
    }
    return (0);
}
