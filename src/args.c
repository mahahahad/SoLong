/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:50:17 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/15 15:41:26 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_ext_valid(char *file)
{
	int	i;

	i = strlen(file) - 4;
	if (i <= 0)
		return (false);
	while (i--)
		file++;
	if (ft_strcmp(file, ".ber") == 0)
		return (true);
	return (false);
}

int	parse_args(int argc, char *argv[])
{
	if (argc != 2 || !argv[1][0])
	{
		ft_error("Please enter the map you would like to use");
		exit(1);
		return (1);
	}
	if (!is_ext_valid(argv[1]))
	{
		ft_error("Please input a map with a .ber file format");
		exit(1);
		return (1);
	}
	return (0);
}
