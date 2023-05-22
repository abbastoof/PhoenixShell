/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:22:37 by atoof             #+#    #+#             */
/*   Updated: 2023/01/17 18:30:37 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_new_line(char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	str = ft_calloc((ft_strlen(s) - i + 1), sizeof(char *));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		str[j++] = s[i++];
	free(s);
	return (str);
}

static char	*ft_get_line(char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	str = ft_calloc(i + 2, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		str[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
		str[i++] = '\n';
	return (str);
}

static char	*ft_read_and_store(int fd, char *cached_str)
{
	char	*read_store;
	int		nbytes;
	char	*tmp;

	if (!cached_str)
		cached_str = ft_calloc(1, 1);
	read_store = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!read_store)
		return (NULL);
	nbytes = 1;
	while (nbytes > 0)
	{
		nbytes = read(fd, read_store, BUFFER_SIZE);
		if (nbytes == -1)
			return (NULL);
		read_store[nbytes] = 0;
		tmp = ft_strjoin(cached_str, read_store);
		free(cached_str);
		cached_str = tmp;
		if (ft_strchr(cached_str, '\n'))
			break ;
	}
	free(read_store);
	return (cached_str);
}

char	*get_next_line(int fd)
{
	static char	*cached_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	cached_str = ft_read_and_store(fd, cached_str);
	if (!cached_str)
		return (NULL);
	line = ft_get_line(cached_str);
	cached_str = ft_new_line(cached_str);
	return (line);
}
