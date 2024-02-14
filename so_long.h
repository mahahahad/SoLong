/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2024/02/13 23:15:19 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef PLAYER_HEIGHT
#  define PLAYER_HEIGHT 64
# endif

# ifndef PLAYER_WIDTH
#  define PLAYER_WIDTH 64
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define WALL '1'
# define EMPTY '0'
# define EXIT 'E'
# define PLAYER 'P'
# define COLLECTABLE 'C'

# ifdef __linux__
// Linux keycodes
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_ARROW_UP 65362
#  define KEY_ARROW_LEFT 65361
#  define KEY_ARROW_DOWN 65364
#  define KEY_ARROW_RIGHT 65363
# else
// macOS key code macros
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_Q 12
#  define KEY_ARROW_UP 126
#  define KEY_ARROW_LEFT 123
#  define KEY_ARROW_DOWN 125
#  define KEY_ARROW_RIGHT 124
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifdef __linux__
#  include "mlx_linux/mlx.h"
#  include <X11/Xlib.h>
#  include <X11/keysym.h>
# else
#  include "mlx_mac/mlx.h"
# endif

typedef struct s_player
{
	int			x;
	int			y;
	int			direction;
}				t_player;

typedef struct s_map
{
	int			fd;
	int			height;
	int			width;
	char		**full;
	int			rows;
	int			columns;
}				t_map;

typedef struct s_collectable
{
	int	collected;
	int	total;
}		t_collectables;

/**
 * @brief Structure that holds all the variables related to the game
 * 
 */
typedef struct s_game
{
	void		*player_up_texture;
	void		*player_down_texture;
	void		*player_left_texture;
	void		*player_right_texture;
	void		*empty_texture;
	void		*wall_texture;
	void		*collectable_texture;
	void		*exit_texture;
	t_collectables	collectables;
	t_player	player;
	t_map		map;
	int			moves;
}				t_game;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_game		game;
}				t_data;

char	*get_next_line(int fd);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*read_map(t_data *data);
void	print_arr(char **arr, int rows, int cols);
char	*ft_itoa(int n);

#endif
