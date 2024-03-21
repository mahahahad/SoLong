/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:14 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/21 12:46:00 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_putstr_endl(char *str, int fd);
void	ft_putnbr(int n);
void	ft_putstr(char *str);
int		ft_error(char *msg);
char	*get_next_line(int fd);
char	**ft_make_2d_arr(int col, int row, char fill_char);
void	ft_free_2d_arr(char **arr);
char	**ft_tabdup(char **tab);
int		ft_get_tab_size(char **tab);
void	ft_get_char_pos(char **tab, char c, int *x, int *y);

#endif
