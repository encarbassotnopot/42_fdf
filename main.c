// Written by Bruh

#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "libft.h"
#include "ft_printf.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	ft_printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}


/*static void key_hook();*/

int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	/*mlx_set_setting(MLX_MAXIMIZED, true);*/
	mlx_t* mlx = mlx_init(WIDTH * 4, HEIGHT * 4, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
