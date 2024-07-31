/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:51:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/07/31 15:33:31 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct point
{
	uint32_t x;
	uint32_t y;
} t_point;

int		get_rgba(int r, int g, int b, int a);
int		get_r(int rgba);
void	set_r(int *rgba, int new_r);
int		get_g(int rgba);
void	set_g(int *rgba, int new_g);
int		get_b(int rgba);
void	set_b(int *rgba, int new_b);
int		get_a(int rgba);
void	set_a(int *rgba, int new_a);
#endif
