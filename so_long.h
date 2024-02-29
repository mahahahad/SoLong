/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2024/02/29 15:27:20 by maabdull         ###   ########.fr       */
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
# define COLLECTIBLE 'C'

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
# include <stdbool.h>
# include <time.h>

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

typedef struct	s_collectable
{
	int			collected;
	int			total;
}				t_collectables;

typedef struct					s_sprite_animated
{
	void						*texture;
	struct s_sprite_animated	*next;
}								t_sprite_animated;

typedef struct			s_textures
{
	t_sprite_animated	*collectible;
	t_sprite_animated	*player;
	t_sprite_animated	*wall;
	t_sprite_animated	*empty;
	t_sprite_animated	*exit;
	t_sprite_animated	*border;
	t_sprite_animated	*asteroid_1;
	t_sprite_animated	*asteroid_2;
	t_sprite_animated	*alien;
}						t_textures;

typedef struct		s_tile
{
	int				x;
	int				y;
}					t_tile;

typedef struct	s_path
{
	t_tile	current_tile;
	struct s_path	*next_tile;
	struct s_path	*prev_tile;
}				t_path;

typedef struct	s_alien
{
	int			x;
	int			y;
	t_path		*path;
}				t_alien;


/**
 * @brief Structure that holds all the variables related to the game
 * 
 */
typedef struct		s_game
{
	t_textures		textures;
	t_collectables	collectables;
	t_player		player;
	t_map			map;
	t_alien			alien;
	int				moves;
}					t_game;

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
bool	check_path(char **map);
int		ft_strcmp(const char *s1, const char *s2);
t_sprite_animated	*init_animated_sprite(t_data data, char *sprite_textures_dir);

#endif
