/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 13:48:48 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/24 17:45:11 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_sdl	*init_sdl()
{
	t_sdl	*sdl;
	
	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	sdl->window = SDL_CreateWindow("DoomNukemTS", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	sdl->surface = SDL_GetWindowSurface(sdl->window);
	return (sdl);
}

t_map	*init_map()
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	// map->field =	"1..............2"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				".......P........"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"4..............3";
					
	// map->field =	"3..............2"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				".......P........"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"1..............4";

	// map->field =	"4..............3"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				".......P........"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"2..............1";

	map->field =	"................"\
					".1.............."\
					"................"\
					".............2.."\
					"................"\
					"................"\
					"................"\
					".......P........"\
					"................"\
					"................"\
					"................"\
					"................"\
					"...4............"\
					"................"\
					"..........3....."\
					"................";

	// map->field =	"................"\
	// 				"..1....2........"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				".......3.....4.."\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"...P............"\
	// 				"................"\
	// 				"................"\
	// 				"................"\
	// 				"..6..........5.."\
	// 				"................"\
	// 				"................";

	map->width = 16;
	map->height = 16;
	return (map);
}

// t_map	*init_map()
// {
// 	t_map		*map;
// 	static int	n = 0;

// 	map = (t_map *)malloc(sizeof(t_map));
// 	if (!n)
// 	{
		
// 	}
	
// 	n += 1;
// 	map->width = 16;
// 	map->height = 16;
// 	return (map);
// }