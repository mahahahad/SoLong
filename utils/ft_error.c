/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdull <maabdull@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:25:57 by maabdull          #+#    #+#             */
/*   Updated: 2024/03/21 13:33:46 by maabdull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_error(char *msg)
{
	ft_putstr_endl("Error", 2);
	ft_putstr_endl(msg, 2);
	return (EXIT_FAILURE);
}
