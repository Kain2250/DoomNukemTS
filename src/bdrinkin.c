/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bdrinkin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 18:20:07 by bdrinkin          #+#    #+#             */
/*   Updated: 2020/10/10 20:20:10 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

size_t			ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		++i;
	}
	return (i);
}

void			ft_putstr(char *s)
{
	if (s != NULL)
		write(1, s, ft_strlen(s));
}

void			ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
}

void			ft_putendl_fd(char const *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd((char *)s, fd);
		write(fd, "\n", 1);
	}
}

int				put_error_sys(char *error)
{
	ft_putendl_fd(error, 2);
	return (1);
}

void			ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (n > 0)
		{
			((char *)s)[i] = '\0';
			++i;
			--n;
		}
	}
	else
		return ;
}

void			*ft_memalloc(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	ft_bzero(str, size);
	return ((void *)str);
}

int				ft_strcmp(const char *s1, const char *s2)
{
	size_t	n;

	n = 0;
	while ((s1[n] != '\0') && (s2[n] != '\0') && (s1[n] == s2[n]))
	{
		n++;
	}
	if ((s1[n] == '\0') && (s2[n] == '\0'))
		return (0);
	else if ((s1[n] == '\0') && (s2[n] != '\0'))
		return (-1);
	else if ((s1[n] != '\0') && (s2[n] == '\0'))
		return (1);
	else
		return (s1[n] - s2[n]);
}

static size_t	wad_len(char *path)
{
	size_t		len;
	size_t		temp_len;
	int			fd;
	uint8_t		*wad_file;

	len = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("file_no_open\n");
		exit(0);
	}
	else
	{
		wad_file = (uint8_t *)ft_memalloc(50 * sizeof(uint8_t));
		temp_len = read(fd, wad_file, 50);
		while (temp_len > 0)
		{
			len += temp_len;
			temp_len = read(fd, wad_file, 50);
		}
		free(wad_file);
	}
	close(fd);
	return (len);
}

static uint8_t	*wad_load(size_t size, char *path)
{
	uint8_t		*data;
	int			fd;

	data = NULL;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("file_no_open\n");
		return (data);
	}
	data = (uint8_t *)malloc((size + 1) * sizeof(uint8_t));
	read(fd, data, size);
	close(fd);
	return (data);
}

void			clear_wad_dir(t_dir *dir)
{
	t_dir		*temp;
	t_dir		*next;

	temp = dir->next;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = NULL;
		temp = next;
	}
	if (dir != NULL)
		free(dir);
}

int16_t		bytes_to_short(const uint8_t *data, int offset)
{
	return ((data[offset + 1] << 8) | data[offset]);
}

uint32_t		bytes_to_int(const uint8_t *data, int offset)
{
	return ((data[offset + 3] << 24) |
			(data[offset + 2] << 16) |
			(data[offset + 1] << 8) | data[offset]);
}

bool			wad_loader(t_wad *doom, char *path)
{
	size_t		len_wad;

	len_wad = wad_len(path);
	doom->map = wad_load(len_wad, path);
	if (doom->map == NULL)
		return (false);
	return (true);
}

void			read_head_data(const uint8_t *data, int offset, t_wad_head *head)
{
	head->wad_type[0] = data[offset];
	head->wad_type[1] = data[offset + 1];
	head->wad_type[2] = data[offset + 2];
	head->wad_type[3] = data[offset + 3];
	head->wad_type[4] = '\0';
	head->dir_count = bytes_to_int(data, offset + 4);
	head->dir_offset = bytes_to_int(data, offset + 8);
}

void			read_dir_data(const uint8_t *data, int offset, t_dir *dir)
{
	dir->lump_offset = bytes_to_int(data, offset);
	dir->lump_size = bytes_to_int(data, offset + 4);
	dir->lump_name[0] = data[offset + 8];
	dir->lump_name[1] = data[offset + 9];
	dir->lump_name[2] = data[offset + 10];
	dir->lump_name[3] = data[offset + 11];
	dir->lump_name[4] = data[offset + 12];
	dir->lump_name[5] = data[offset + 13];
	dir->lump_name[6] = data[offset + 14];
	dir->lump_name[7] = data[offset + 15];
	dir->lump_name[8] = '\0';
}

uint32_t		find_offset_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_offset);
}

uint32_t		find_size_lump(t_dir *dir, char *lable, char *name_map)
{
	t_dir	*temp;

	temp = dir;
	if (name_map != NULL)
		while (temp != NULL && ft_strcmp(name_map, temp->lump_name) != 0)
			temp = temp->next;
	while (temp != NULL && ft_strcmp(lable, temp->lump_name) != 0)
		temp = temp->next;
	if (temp == NULL)
	{
		put_error_sys("Error wadfile - could not find lumpname");
		exit (-1);
	}
	return (temp->lump_size);
}

bool			wad_reader(t_wad *doom)
{
	t_dir		*temp;
	size_t		i;

	i = -1;
	read_head_data(doom->map, 0, &doom->head);
	doom->dir = (t_dir *)ft_memalloc(sizeof(t_dir));
	temp = doom->dir;
	while (++i < doom->head.dir_count)
	{
		read_dir_data(doom->map, doom->head.dir_offset + i * 16, temp);
		if (i + 1 != doom->head.dir_count)
		{
			temp->next = (t_dir *)ft_memalloc(sizeof(t_dir));
			temp = temp->next;
		}
	}
	return (true);
}

void			wad_get_vertex(t_wad *doom, t_vlist *vert, char *name_map)
{
	uint32_t 	offset;
	uint32_t	size;
	uint32_t	temp_offset;
	t_vlist 	*vert_temp;
	int			i;

	offset = find_offset_lump(doom->dir, "VERTEXES", name_map);
	size = find_size_lump(doom->dir, "VERTEXES", name_map);
	temp_offset = offset + size;
	vert_temp = vert;
	i = 0;
	while (offset < temp_offset)
	{
		if (offset + 4 < temp_offset)
			vert_temp->next = (t_vlist *)ft_memalloc(sizeof(t_vlist));
		vert_temp->crd[X] = bytes_to_short(doom->map, offset); //abs((bytes_to_short(doom->map, offset) - 5000) / 20);
		vert_temp->crd[Y] = bytes_to_short(doom->map, offset + 2);// - 5000) / 20;
		vert_temp->index = i;
		vert_temp->data = i + 1;
		offset += 4;
		i++;
		vert_temp = vert_temp->next;
	}
}
