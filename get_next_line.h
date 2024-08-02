/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoma-ba <ecoma-ba@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:16:23 by ecoma-ba          #+#    #+#             */
/*   Updated: 2024/06/30 20:39:00 by ecoma-ba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include <stddef.h>
# include <limits.h>
# define GET_NEXT_LINE_H
# if BUFFER_SIZE < 1LU
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1LU
# endif
# if BUFFER_SIZE > SSIZE_MAX
#  undef BUFFER_SIZE
#  define BUFFER_SIZE SSIZE_MAX
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4LU
# endif

char	*grow_buf(char *old_buf, char *new_buf, size_t buf_size,
			size_t extra_size);

int		get_next_buffer(int fd, char **leftovers, size_t *leftover_size);
char	*get_next_line(int fd);
char	*ft_gnl_strchr(const char *s, int c);
void	*ft_gnl_memcpy(void *dest, const void *src, size_t n);
void	*ft_gnl_calloc(size_t nmemb, size_t size);
void	ft_gnl_bzero(void *ptr, size_t n);
char	*ft_gnl_memdup(char *s, size_t n);
int		ft_gnl_memchr_idx(const char *s, int c, size_t n);
#endif
