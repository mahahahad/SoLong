/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:04 by maabdull          #+#    #+#             */
/*   Updated: 2023/11/14 11:12:05 by maabdull         ###   ########.fr       */
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

// Key code macros
# ifndef KEY_ESC
#  define KEY_ESC 53
# endif
# ifndef KEY_W
#  define KEY_W 13
# endif
# ifndef KEY_A
#  define KEY_A 0
# endif
# ifndef KEY_S
#  define KEY_S 1
# endif
# ifndef KEY_D
#  define KEY_D 2
# endif
# ifndef KEY_Q
#  define KEY_Q 12
# endif
# ifndef KEY_ARROW_UP
#  define KEY_ARROW_UP 126
# endif
# ifndef KEY_ARROW_LEFT
#  define KEY_ARROW_LEFT 123
# endif
# ifndef KEY_ARROW_DOWN
#  define KEY_ARROW_DOWN 125
# endif
# ifndef KEY_ARROW_RIGHT
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
#  include <X11/X.h>
#  include <X11/keysym.h>
# else
#  include "mlx_mac/mlx.h"
# endif

char			*get_next_line(int fd);
void			ft_putstr(char *str);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char const *s2);
char			**ft_split(char const *s, char c);

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
