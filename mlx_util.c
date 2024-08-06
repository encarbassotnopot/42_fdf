/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:57:57 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/06 12:46:23 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_key_hook(mlx_key_data_t kd, void *mlx)
{
	if (kd.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}
