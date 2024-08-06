/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:57:57 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/06 11:40:46 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WIDTH 1024
#define HEIGHT 1024
#define IMG_SCALE 4

void	ft_img_set_pixel(mlx_image_t *img, t_point_d *p, uint32_t color)
{
	int	x;
	int	y;

	if (p->x <= 0 || p->y <= 0)
		return ;
	x = round(p->x * IMG_SCALE);
	y = round(p->y * IMG_SCALE);
	ft_memset32(&img->pixels[x + y * img->width], color, 1);
}

void	draw_line(mlx_image_t *img, t_coord *from, t_coord *to)
{
	t_point_d	*p_diff;
	t_point_d	*p_draw;
	int			step;
	int			i;

	i = -1;
	p_diff = ft_calloc(1, sizeof(t_point_d));
	p_draw = ft_calloc(1, sizeof(t_point_d));
	if (!p_diff || !p_draw)
	{
		free(p_diff);
		free(p_draw);
		return ;
	}
	p_diff->x = from->proj_x - to->proj_x;
	p_diff->y = from->proj_y - to->proj_y;
	p_draw->x = to->proj_x + 10;
	p_draw->y = to->proj_y + 10;
	if (p_diff->x == 0 && p_diff->y == 0)
	{
		ft_img_set_pixel(img, p_draw, 0xFF);
		free(p_diff);
		free(p_draw);
		return ;
	}
	step = fmax(fabs(p_diff->x), fabs(p_diff->y));
	while (++i <= step)
	{
		ft_img_set_pixel(img, p_draw, 0xFF);
		p_draw->x += p_diff->x / step;
		p_draw->y += p_diff->y / step;
	}
	free(p_diff);
	free(p_draw);
}

void	draw_map(mlx_image_t *img, t_coord *map, int color)
{
	t_coord	*iter;
	t_coord	*line_h;

	ft_memset32(img->pixels, color, img->width * img->height);
	line_h = map;
	while (line_h)
	{
		iter = line_h;
		while (iter)
		{
			if (iter->next_x)
				draw_line(img, iter->next_x, iter);
			if (iter->next_z)
				draw_line(img, iter, iter->next_z);
			iter = iter->next_x;
		}
		line_h = line_h->next_z;
	}
}

void	ft_key_hook(mlx_key_data_t kd, void *mlx)
{
	if (kd.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}

int32_t	mlx_main(t_coord *map, t_limits *l)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init((l->max_x - l->min_x + 20), (l->max_y - l->min_y + 20),
			"test", true);
	if (!mlx)
	{
		ft_printf("MLX Error: %s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, (l->max_x - l->min_x) * IMG_SCALE + 20, (l->max_y
				- l->min_y) * IMG_SCALE + 20);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		ft_printf("MLX Error: %s\n", mlx_strerror(mlx_errno));
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	draw_map(img, map, 0xF05B3CFF);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}
