// Written by Bruh

#include "MLX42/MLX42.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void	ft_error(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void	ft_hook(void *param)
{
	int			aug;
	static int	color = 0;
	mlx_image_t	*img;

	int32_t x, y;
	aug = 3;
	/*mlx_get_window_pos(mlx, &x, &y);*/
	/*if (mlx_is_key_down(param, MLX_KEY_LEFT_SHIFT))*/
	/*	aug *= 5;*/
	/*if (mlx_is_key_down(param, MLX_KEY_UP))*/
	/*	y -= aug;*/
	/*if (mlx_is_key_down(param, MLX_KEY_DOWN))*/
	/*	y += aug;*/
	/*if (mlx_is_key_down(param, MLX_KEY_LEFT))*/
	/*	x -= aug;*/
	/*if (mlx_is_key_down(param, MLX_KEY_RIGHT))*/
	/*	x += aug;*/
	/*mlx_set_window_pos(mlx, x, y);*/
	//
	img = (mlx_image_t *)param;
	color += 3;
	color %= 0x1000000;
	ft_memset(img->pixels, (color << 8), img->width * img->height
		* sizeof(int32_t));
	ft_printf("color: %#x\n", img->pixels[0]);
}

static void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	ft_printf("key %d, action %d, os %d, modifier %d\n", keydata.key,
		keydata.action, keydata.os_key, keydata.modifier);
}

static void	ft_cursor_hook(double xpos, double ypos, void *param)
{
	ft_printf("x %d, y %d\n", xpos, ypos);
}

static void	ft_scroll_hook(double xdelta, double ydelta, void *param)
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	printf("x %f, y %f\n", xdelta, ydelta);
}

static void	ft_mouse_hook(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	ft_printf("key %d, action %d, modifier %d\n", button, action, mods);
}

/*static void key_hook();*/

int32_t	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*arr[2];

	// MLX allows you to define its core behaviour before startup.
	/*mlx_set_setting(MLX_MAXIMIZED, true);*/
	mlx = mlx_init(WIDTH * 4, HEIGHT * 4, "test", true);
	if (!mlx)
		ft_error();
	/* Do stuff */
	// Create and display the image.
	img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
	// Even after the image is being displayed, we can still modify the buffer.
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	arr[0] = mlx;
	arr[1] = img;
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_key_hook(mlx, ft_key_hook, mlx);
	mlx_mouse_hook(mlx, ft_mouse_hook, mlx);
	mlx_scroll_hook(mlx, ft_scroll_hook, mlx);
	mlx_cursor_hook(mlx, ft_cursor_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
