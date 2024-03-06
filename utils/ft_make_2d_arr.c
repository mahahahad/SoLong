/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_2d_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:09:09 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/06 18:19:24 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

/**
 * @brief Creates a 2d array of size row and col.
 * Initializes it with fill_char
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
	int		i;
	int		j;

	i = 0;
	string = NULL;
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
	dup_arr[i] = NULL;
	return (dup_arr);
}
