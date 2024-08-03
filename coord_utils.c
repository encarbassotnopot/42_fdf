/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:21:42 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/08/03 14:36:47 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	*new_coord(double x, double y, double z)
{
	t_coord	*coord;

	coord = ft_calloc(1, sizeof(t_coord));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

void	link_hor(t_coord **head, t_coord *last)
{
	t_coord	*iter;

	iter = *head;
	while (iter->z < last->z)
	{
		if (iter->next_z)
			iter = iter->next_z;
		else
		{
			iter->next_z = last;
			return ;
		}
	}
	while (iter->x < last->x)
	{
		if (iter->next_x)
			iter = iter->next_x;
		else
		{
			iter->next_x = last;
			return ;
		}
	}
}

void	link_vert(t_coord **head, t_coord *last)
{
	t_coord	*iter;

	iter = *head;
	while (iter->x < last->x)
	{
		if (iter->next_x)
			iter = iter->next_x;
		else
			break ;
	}
	while (iter->z < last->z)
	{
		if (iter->next_z)
			iter = iter->next_z;
		else
		{
			iter->next_z = last;
			return ;
		}
	}
}

void	append_coord(t_coord **head, t_coord *last)
{
	t_coord	*iter;

	if (!*head)
	{
		*head = last;
		return ;
	}
	link_hor(head, last);
	link_vert(head, last);
}

void	free_coords(t_coord **head)
{
	t_coord	*new;
	t_coord	*line_h;
	t_coord	*line_h_next;
	t_coord	*prev;

	line_h = *head;
	while (line_h)
	{
		new = line_h;
		line_h_next = line_h->next_z;
		while (new)
		{
			prev = new;
			new = new->next_x;
			free(prev);
		}
		line_h = line_h_next;
	}
	*head = NULL;
}
