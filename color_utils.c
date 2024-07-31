/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:50:01 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/07/31 12:54:35 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_r(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

void	set_r(int *rgba, int new_r)
{
	if (rgba)
		*rgba = (*rgba & ~(0xFF << 24)) + ((new_r & 0xFF) << 24);
}

int	get_g(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

void	set_g(int *rgba, int new_g)
{
	if (rgba)
		*rgba = (*rgba & ~(0xFF << 16)) + ((new_g & 0xFF) << 16);
}

int	get_b(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

void	set_b(int *rgba, int new_b)
{
	if (rgba)
		*rgba = (*rgba & ~(0xFF << 8)) + ((new_b & 0xFF) << 8);
}

int	get_a(int rgba)
{
	return (rgba & 0xFF);
}

void	set_a(int *rgba, int new_a)
{
	if (rgba)
		*rgba = *rgba & ~0xFF + new_a & 0xFF;
}
