/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:57:57 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/02 09:08:51 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define WIDTH 1024
#define HEIGHT 1024

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
	x = p->x * 4;
	y = p->y * 4;
	ft_memset32(&img->pixels[x + y * img->width], color, 1);
}

static void	ft_key_hook(mlx_key_data_t kd, void **arr)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			*last_col;
	int			*color;
	int			aug;

	aug = 1;
	mlx = arr[0];
	img = arr[1];
	color = arr[2];
	last_col = arr[3];
	if (kd.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
	if (kd.key == MLX_KEY_R)
		ft_memset32(img->pixels, *color, img->width * img->height);
	ft_printf("key %d, action %d, os %d, modifier %d\n", kd.key, kd.action,
		kd.os_key, kd.modifier);
}

static void	draw_line(mlx_image_t *img, t_point **p, uint32_t color)
{
	t_point_d	*p_diff;
	t_point_d	*p_draw;
	t_point		*p_round;
	int			step;
	int			i;

	i = -1;
	p_diff = ft_calloc(1, sizeof(t_point_d));
	p_diff->x = p[1]->x - p[0]->x;
	p_diff->y = p[1]->y - p[0]->y;
	p_draw = ft_calloc(1, sizeof(t_point_d));
	p_draw->x = p[0]->x;
	p_draw->y = p[0]->y;
	p_round = ft_calloc(1, sizeof(t_point));
	if (p_diff->x == 0 && p_diff->y == 0)
	{
		free(p_diff);
		free(p_draw);
		return ;
	}
	if (abs(p_diff->x) > abs(p_diff->y))
		step = p_diff->x;
	else
		step = p_diff->y;
	p_diff->x /= step;
	p_diff->y /= step;
	while (++i < step)
	{
		p_round->x = round(p_draw->x);
		p_round->y = round(p_draw->y);
		ft_img_set_pixel(img, p_round, color);
		p_draw->x += p_diff->x;
		p_draw->y += p_diff->y;
		ft_printf("x1: %d, y1: %d\n", p_draw->x, p_draw->y);
	}
	free(p_diff);
	free(p_draw);
	free(p_round);
}

static void	ft_mouse_hook(mouse_key_t button, action_t action,
		modifier_key_t mods, void **arr)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			*last_col;
	int			*color;
	int			aug;
	t_point		**points;

	mlx = arr[0];
	int x, y;
	img = arr[1];
	color = arr[2];
	points = (t_point **)arr[4];
	ft_printf("key %d, action %d, modifier %d\n", button, action, mods);
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		mlx_get_mouse_pos(mlx, &points[0]->x, &points[0]->y);
		ft_printf("x: %d, y: %d\n", points[1]->x, points[1]->y);
		draw_line(img, points, 0xFF);
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		mlx_get_mouse_pos(mlx, &points[1]->x, &points[1]->y);
		ft_printf("x: %d, y: %d\n", points[0]->x, points[0]->y);
		draw_line(img, points, 0xFF);
	}
}
/*
int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			color;
	void		*arr[5];
	t_point		**points;

	points = ft_calloc(2, sizeof(t_point *));
	points[0] = ft_calloc(1, sizeof(t_point));
	points[1] = ft_calloc(1, sizeof(t_point));
	color = 0xF05B3CFF;
	mlx = mlx_init(WIDTH, HEIGHT, "test", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH * 4, HEIGHT * 4);
	ft_memset32(img->pixels, color, img->width * img->height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	arr[0] = mlx;
	arr[1] = img;
	arr[2] = &color;
	arr[4] = points;
	mlx_resize_hook(mlx, ft_resize_hook, arr);
	mlx_mouse_hook(mlx, ft_mouse_hook, arr);
	mlx_key_hook(mlx, ft_key_hook, arr);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}*/
