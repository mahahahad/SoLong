/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2023/11/07 12:09:22 by maabdull         ###   ########.fr       */
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

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifdef __linux__
#  include "mlx_linux/mlx.h"
#  include <X11/X.h>
#  include <X11/keysym.h>
# else
#  include "mlx_mac/mlx.h"
# endif

typedef struct s_player
{
	int			pos_x;
	int			pos_y;
	int			player_pos_x;
	int			player_pos_y;
}				t_player;

typedef struct s_map
{
	int			fd;
	int			height;
	int			width;
	char		*path;
}				t_map;

typedef struct s_game
{
	void		*player_texture;
	void		*empty_texture;
	void		*wall_texture;
	void		*collectable_texture;
	void		*exit_texture;
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

#endif
