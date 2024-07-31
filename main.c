/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:57:57 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/07/31 16:48:33 by ecoma-ba         ###   ########.fr       */
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
	/*mlx_resize_image(img, width, height);*/
}

static void	ft_img_set_pixel(mlx_t *mlx, mlx_image_t *img, t_point *p,
		uint32_t color)
{
	int	x;
	int	y;

	if (p->x <= 0 || p->y <= 0)
		return ;
	x = p->x*4;
	y = p->y*4;
	ft_memset32(&img->pixels[x + y * img->width], color, 1);
}

static void	ft_key_hook_line(mlx_key_data_t kd, void **arr)
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
		ft_printf("x: %d, y: %d\n", points[0]->x, points[0]->y);
		ft_img_set_pixel(mlx, img, points[0], 0xFF);
	}
	if (button == MLX_MOUSE_BUTTON_RIGHT)
	{
		mlx_get_mouse_pos(mlx, &points[1]->x, &points[1]->y);
		ft_printf("x: %d, y: %d\n", points[1]->x, points[1]->y);
		ft_img_set_pixel(mlx, img, points[1], 0xFFFFFFFF);
	}
}

static void	ft_hook(void **arr)
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
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, &points[0]->x, &points[0]->y);
		ft_printf("x: %d, y: %d\n", points[0]->x, points[0]->y);
		ft_img_set_pixel(mlx, img, points[0], 0xFF);
	}
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_RIGHT))
	{
		mlx_get_mouse_pos(mlx, &points[1]->x, &points[1]->y);
		ft_printf("x: %d, y: %d\n", points[1]->x, points[1]->y);
		ft_img_set_pixel(mlx, img, points[1], 0xFFFFFFFF);
	}
}

int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			color;
	int			last_color;
	void		*arr[5];
	t_point		**points;
	t_point		*point;
	int			i;
	int			j;

	points = ft_calloc(2, sizeof(t_point *));
	points[0] = ft_calloc(1, sizeof(t_point));
	points[1] = ft_calloc(1, sizeof(t_point));
	point = ft_calloc(1, sizeof(t_point));
	color = 0xF05B3CFF;
	last_color = color;
	mlx = mlx_init(WIDTH, HEIGHT, "test", true);
	if (!mlx)
		ft_error();
	img = mlx_new_image(mlx, WIDTH*4, HEIGHT*4);
	ft_memset32(img->pixels, color, img->width * img->height);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	i = -1;
	j = -1;

	arr[0] = mlx;
	arr[1] = img;
	arr[2] = &color;
	arr[3] = &last_color;
	arr[4] = points;
	mlx_loop_hook(mlx, ft_hook, arr);
	mlx_resize_hook(mlx, ft_resize_hook, arr);
	mlx_mouse_hook(mlx, ft_mouse_hook, arr);
	mlx_key_hook(mlx, ft_key_hook_line, arr);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (MLX_SUCCESS);
}
