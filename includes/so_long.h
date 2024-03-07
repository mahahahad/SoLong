/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/05 21:49:11 by maabdull         ###   ########.fr       */
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
#  define OFFSET 64
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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "utils.h"

typedef struct s_player
{
	int							x;
	int							y;
}								t_player;

typedef struct s_map
{
	int							fd;
	int							height;
	int							width;
	char						**full;
	int							rows;
	int							columns;
}								t_map;

typedef struct s_collectable
{
	int							collected;
	int							total;
}								t_collectables;

typedef struct s_sprite_animated
{
	void						*texture;
	struct s_sprite_animated	*next;
}								t_sprite_animated;

typedef struct s_textures
{
	t_sprite_animated			*collectible;
	t_sprite_animated			*player;
	t_sprite_animated			*wall;
	t_sprite_animated			*empty;
	t_sprite_animated			*exit;
	t_sprite_animated			*border;
	t_sprite_animated			*asteroid_1;
	t_sprite_animated			*asteroid_2;
	t_sprite_animated			*alien;
}								t_textures;

typedef struct s_tile
{
	int							x;
	int							y;
}								t_tile;

typedef struct s_path
{
	t_tile						*current_tile;
	struct s_path				*next_tile;
	struct s_path				*prev_tile;
}								t_path;

typedef struct s_alien
{
	t_path						*path;
}								t_alien;

typedef struct s_game
{
	t_textures					*textures;
	t_collectables				*collectables;
	t_player					*player;
	t_map						*map;
	t_alien						*alien;
	int							move_count;
	int							exit_count;
	int							player_count;
}								t_game;

typedef struct s_data
{
	void						*mlx_ptr;
	void						*win_ptr;
	t_game						*game;
}								t_data;

int					check_map(t_data *data);
int					read_map(t_data *data);
int					render_map(t_data *data);
int					update_map(t_data *data);
bool				check_path(char **map);
t_sprite_animated	*init_animated_sprite(t_data data,
						char *sprite_textures_dir);
int					parse_args(int argc, char *argv[]);
void				free_data_struct(t_data *data);
void				free_alien_path(t_data *data);
int					get_exit_coordinates(t_data *data, int *x, int *y);
int					get_free_space(t_data *data, int x, int y,
						t_tile *free_space[]);
int					display_enemy(t_data *data);
void				move_enemy(t_data *data);
t_path				*initialize_enemy_path(t_data *data);
int					handle_keypress(int keysym, t_data *data);
int					handle_destroy(t_data *data);
int					move_to(t_data *data, int new_x, int new_y);

#endif
