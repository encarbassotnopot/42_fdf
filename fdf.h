/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:51:05 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/06 11:43:33 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include "MLX42/MLX42.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <float.h>
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

char				*get_next_line(int fd);
t_coord				*new_coord(double x, double y, double z);
void				append_coord(t_coord **head, t_coord *last);
void				free_coords(t_coord **head);
int32_t				mlx_main(t_coord *map, t_limits *l);
void				calculate_2d(t_coord *c, t_limits *l);
int					parse_line(t_coord **map, char *line, int z, t_limits *l);
int					parse_map(t_coord **map, int fd, t_limits *l);
void				normalize_proj(t_coord *map, t_limits *limits);
t_limits			*init_limits(void);
#endif
