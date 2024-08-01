/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:51:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/01 14:19:31 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct point
{
	int32_t	x;
	int32_t	y;
}				t_point;

typedef struct point_d
{
	double	x;
	double	y;
}				t_point_d;

int				get_rgba(int r, int g, int b, int a);
int				get_r(int rgba);
void			set_r(int *rgba, int new_r);
int				get_g(int rgba);
void			set_g(int *rgba, int new_g);
int				get_b(int rgba);
void			set_b(int *rgba, int new_b);
int				get_a(int rgba);
void			set_a(int *rgba, int new_a);
#endif
