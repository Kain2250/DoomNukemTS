/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdrinkin <bdrinkin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:11:05 by jthuy             #+#    #+#             */
/*   Updated: 2020/10/10 19:22:24 by bdrinkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "SDL.h"
# include "SDL_image.h"
# include "SDL_mixer.h"

typedef struct			s_wad_head
{
	char				wad_type[5];
	uint32_t			dir_count;
	uint32_t			dir_offset;
}						t_wad_head;

typedef struct			s_dir
{
	uint32_t			lump_offset;
	uint32_t			lump_size;
	char				lump_name[9];
	struct s_dir		*next;
}						t_dir;

typedef struct			s_wad
{
	uint8_t				*map;
	struct s_dir		*dir;
	struct s_wad_head	head;
}						t_wad;


typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Event		event;
}					t_sdl;

typedef struct	s_player
{
	int			index;
	int			crd[2];
	double		direction;
	int			pastcrd[2];
}				t_player;

typedef struct	s_map
{
	char		*field;
	int			width;
	int			height;
	int			scale_vert[2][2];
}				t_map;

typedef struct		s_vlist
{
	int				data;
	int				index;
	int				crd[2];
	struct s_vlist	*next;
}					t_vlist;

typedef struct		s_llist
{
	int				crd[2][2];
	int				k[3];
	double			direct;
	double			normal;
	struct s_llist	*next;
}					t_llist;

typedef struct		s_bsp
{
	double			crd[2][2];
	double			proj[2];
	double			len;
	double			pivot[2];
	double			direct;
	double			normal;
	int				k[3];
	struct s_bsp	*front;
	struct s_bsp	*back;
}					t_bsp;

#endif