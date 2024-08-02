/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:51:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/02 15:56:13 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct point
{
	int32_t			x;
	int32_t			y;
}					t_point;

typedef struct point_d
{
	double			x;
	double			y;
}					t_point_d;

typedef struct coord
{
	double			x;
	double			y;
	double			z;
	double			proj_x;
	double			proj_y;
	struct coord	*next_x;
	struct coord	*next_z;
}					t_coord;

typedef struct limits
{
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
}					t_limits;

int					get_rgba(int r, int g, int b, int a);
int					get_r(int rgba);
void				set_r(int *rgba, int new_r);
int					get_g(int rgba);
void				set_g(int *rgba, int new_g);
int					get_b(int rgba);
void				set_b(int *rgba, int new_b);
int					get_a(int rgba);
void				set_a(int *rgba, int new_a);
char				*get_next_line(int fd);
t_coord				*new_coord(double x, double y, double z);
void				append_coord(t_coord **head, t_coord *last);
void				free_coords(t_coord **head);
int32_t				mlx_main(t_coord *map, t_limits *l);
#endif
