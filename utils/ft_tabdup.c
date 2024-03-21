/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:36:47 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/21 13:00:40 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Duplicates the provided 2d arr
 *
 * @param tab
 * @return char**
 */
char	**ft_tabdup(char **tab)
{
	char	**new_tab;
	int		y;

	if (!tab || !tab[0][0])
		return (NULL);
	y = 0;
	new_tab = malloc((ft_get_tab_size(tab) * ft_strlen(tab[0])) + 1);
	while (tab[y])
	{
		new_tab[y] = ft_strdup(tab[y]);
		y++;
	}
	new_tab[y] = NULL;
	return (new_tab);
}
