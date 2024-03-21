/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:49:58 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/21 11:51:26 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Gets the index of the first occurence of the specified
 * char in the 2d arr
 * 
 * @param tab The 2d arr to search within
 * @param char The character to find
 * @param int *x The variable that will store the x index
 * @param int *y The variable that will store the y index
 */
void	ft_get_char_pos(char **tab, char c, int *x, int *y)
{
	int	i;
	int	j;
	int	rows;
	int	columns;

	i = 0;
	rows = ft_get_tab_size(tab);
	columns = ft_strlen(tab[0]);
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (tab[i][j] == c)
			{
				*x = j;
				*y = i;
				break ;
			}
			j++;
		}
		i++;
	}
}
