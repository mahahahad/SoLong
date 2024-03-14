/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/14 13:51:11 by maabdull         ###   ########.fr       */
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

# ifndef OFFSET
#  define OFFSET 32
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

# include "../mlx/mlx.h"
# include "utils.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# ifdef __linux__
# include <X11/Xlib.h>
# include <X11/keysym.h>
# endif

typedef struct s_player
{
	int				x;
	int				y;
}					t_player;

typedef struct s_map
{
	int				fd;
	char			**full;
	int				rows;
	int				columns;
}					t_map;

typedef struct s_collectable
{
	int				collected;
	int				total;
}					t_collectables;

typedef struct s_textures
{
	void		*border_0;
	void		*border_1;
	void		*border_2;
	void		*border_3;
	void		*border_4;
	void		*border_5;
	void		*border_6;
	void		*border_7;
	void		*player;
	void		*collectible;
	void		*exit;
	void		*wall;
	void		*enemy;
	void		*empty;
}					t_textures;

typedef struct s_game
{
	t_textures		*textures;
	t_collectables	*collectables;
	t_player		*player;
	t_map			*map;
	int				move_count;
	int				exit_count;
	int				player_count;
}					t_game;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_game			*game;
}					t_data;

int					parse_args(int argc, char *argv[]);
int					read_map(t_data *data);
int					check_map(t_data *data);
bool				check_path(t_data *data, char **map);
void				*check_wall_texture(t_data *data, int x, int y);
void				*check_texture(t_data *data, int x, int y);
void				render_texture(t_data *data, void *texture, int x, int y);
int					render_map(t_data *data);
int					calculate_frame(t_data *data);
int					get_exit_coordinates(t_data *data, int *x, int *y);
void				free_enemy_path(t_data *data);
int					display_enemy(t_data *data);
void				move_enemy(t_data *data);
int					move_to(t_data *data, int new_x, int new_y);
int					handle_keypress(int keysym, t_data *data);
int					handle_destroy(t_data *data);
bool				have_textures_loaded(t_data *data);
int					init_map_struct(t_data *data);
int					init_data_struct(t_data *data);
void				free_data_struct(t_data *data);
void				free_textures(t_data *data);
void				load_borders(t_data *data);

#endif
