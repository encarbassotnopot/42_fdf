/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:07:13 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/06/27 10:49:32 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// grows a buffer by appending a new buffer to it.
char	*grow_buf(char *old_buf, char *new_buf, size_t buf_size,
		size_t extra_size)
{
	char	*buf;

	if (!old_buf)
		buf_size = 0;
	if (extra_size < 1)
		return (old_buf);
	buf = ft_gnl_calloc(buf_size + extra_size, sizeof(char));
	if (!buf)
		return (NULL);
	if (old_buf)
		ft_gnl_memcpy(buf, old_buf, buf_size);
	ft_gnl_memcpy(&(buf[buf_size]), new_buf, extra_size);
	free(old_buf);
	return (buf);
}

int	return_on_error(void *to_free, int return_value)
{
	free(to_free);
	return (return_value);
}

// reads in BUFFER_SIZE'd chunks from fd, until a \n is read (or file ends)
// writes to leftovers and updates it's size
// returns 0 if everything is ok, 1 on file error/end, 2 on malloc error.
int	get_next_buffer(int fd, char **leftovers, size_t *leftover_size)
{
	char	*new_buf;
	ssize_t	read_bytes;

	read_bytes = BUFFER_SIZE;
	new_buf = ft_gnl_calloc(BUFFER_SIZE, 1);
	if (!new_buf)
		return (1);
	while (ft_gnl_memchr_idx(new_buf, '\n', read_bytes) == -1
		&& read_bytes == BUFFER_SIZE)
	{
		read_bytes = read(fd, new_buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (return_on_error(new_buf, 1));
		*leftovers = grow_buf(*leftovers, new_buf, *leftover_size, read_bytes);
		if (!*leftovers)
			return (return_on_error(new_buf, 2));
		*leftover_size += read_bytes;
	}
	free(new_buf);
	return (0);
}

// handles the leftovers after a line is selected to be printed.
// if there are no leftovers, it frees them. otherwise it copies them to
// the start of the leftover accomulator.
// returns 1 on error.
int	manage_leftovers(char **leftovers, size_t leftover_size, int line_len)
{
	char	*tempovers;

	if (leftover_size == 0)
	{
		free(*leftovers);
		*leftovers = NULL;
	}
	else
	{
		tempovers = *leftovers;
		*leftovers = ft_gnl_memdup(tempovers + line_len, leftover_size);
		if (!*leftovers)
			return (1);
		free(tempovers);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*leftovers = NULL;
	static size_t	leftover_size = 0;
	char			*line;
	int				line_len;

	if (fd < 0)
		return (NULL);
	if (!leftovers || leftover_size == 0 || ft_gnl_memchr_idx(leftovers, '\n',
			leftover_size) == -1)
		if (get_next_buffer(fd, &leftovers, &leftover_size) > 0)
			return (NULL);
	line_len = ft_gnl_memchr_idx(leftovers, '\n', leftover_size) + 1;
	if (line_len == 0)
		line_len = leftover_size;
	line = ft_gnl_memdup(leftovers, line_len);
	line = grow_buf(line, "\0", line_len, 1);
	leftover_size -= line_len;
	if (manage_leftovers(&leftovers, leftover_size, line_len) != 0)
		return (NULL);
	return (line);
}
