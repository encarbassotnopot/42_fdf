/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:57:57 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/02 16:32:57 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WIDTH 1024
#define HEIGHT 1024
#define IMG_SCALE 12

// Exit the program as failure.
static void	ft_error(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void	ft_resize_hook(int32_t width, int32_t height, void **arr)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = arr[0];
	img = arr[1];
	mlx_resize_image(img, width, height);
}

static void	ft_img_set_pixel(mlx_image_t *img, t_point *p, uint32_t color)
{
	int	x;
	int	y;

	if (p->x <= 0 || p->y <= 0)
		return ;
	x = p->x*IMG_SCALE;
	y = p->y*IMG_SCALE;
	ft_memset32(&img->pixels[x + y * img->width], color, 1);
}


static void	draw_line(mlx_image_t *img, t_coord *from, t_coord *to, t_limits *l)
{
	t_point_d	*p_diff;
	t_point_d	*p_draw;
	t_point		*p_round;
	int			step;
	int			i;

	i = -1;
	p_diff = ft_calloc(1, sizeof(t_point_d));
	p_diff->x = from->proj_x - to->proj_x - l->min_x + 10;
	p_diff->y = from->proj_y - to->proj_y - l->min_y + 10;
	p_draw = ft_calloc(1, sizeof(t_point_d));
	p_draw->x = to->x - l->min_x + 10;
	p_draw->y = to->y - l->min_y + 10;
	p_round = ft_calloc(1, sizeof(t_point));
	if (p_diff->x == 0 && p_draw->y == 0)
	{
		ft_img_set_pixel(img, p_round, 0xFF);
		free(p_diff);
		free(p_draw);
		return ;
	}
	printf("from: %f,%f to %f,%f\n", from->proj_x, from->proj_y, to->proj_x,
		to->proj_y);
	if (fabs(p_diff->x) > fabs(p_diff->y))
		step = p_diff->x;
	else
		step = p_diff->y;
	p_diff->x /= step;
	p_diff->y /= step;
	while (++i < step)
	{
		p_round->x = round(p_draw->x);
		p_round->y = round(p_draw->y);
		ft_img_set_pixel(img, p_round, 0xFF);
		p_draw->x += p_diff->x;
		p_draw->y += p_diff->y;
	}
	free(p_diff);
	free(p_draw);
	free(p_round);
}

void	map_next(mlx_image_t *img, t_coord *map, t_limits *l, int reset)
{
	static t_coord	*iter = NULL;
	static t_coord	*line_h = NULL;

	if (!iter || reset)
	{
		line_h = map;
		iter = line_h;
	}
	if (line_h)
	{
		if (iter)
		{
			if (iter->next_x)
				draw_line(img, iter, iter->next_x, l);
			if (iter->next_z)
				draw_line(img, iter, iter->next_z, l);
			iter = iter->next_x;
		}
		line_h = line_h->next_z;
		if (!iter)
			iter = line_h;
	}
}

void	ft_draw_next_line(void **arr)
{
	map_next(arr[1], arr[2], arr[3], 0);
}

static void	ft_key_hook(mlx_key_data_t kd, void **arr)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			*last_col;
	int			aug;

	aug = 1;
	mlx = arr[0];
	/*img = arr[1];*/
	if (kd.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
	if (kd.key == MLX_KEY_R)
	{
		ft_memset32(img->pixels, 0xFFFFFFFF, img->width * img->height);
		map_next(arr[1], arr[2], arr[3], 1);
	}
	ft_printf("key %d, action %d, os %d, modifier %d\n", kd.key, kd.action,
		kd.os_key, kd.modifier);
}
int32_t	mlx_main(t_coord *map, t_limits *l)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*arr[4];
	int			color;

	color = 0xF05B3CFF;
	color = 0xFFFFFFFF;
	mlx = mlx_init((l->max_x - l->min_x + 20), (l->max_y - l->min_y + 20),
			"test", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, (l->max_x - l->min_x + 20) * IMG_SCALE, (l->max_y
				- l->min_y + 20) * IMG_SCALE);
	ft_memset32(img->pixels, color, img->width * img->height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	arr[0] = mlx;
	arr[1] = img;
	arr[2] = map;
	arr[3] = l;
	mlx_resize_hook(mlx, ft_resize_hook, arr);
	mlx_key_hook(mlx, ft_key_hook, arr);
	mlx_loop_hook(mlx, ft_draw_next_line, arr);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}
