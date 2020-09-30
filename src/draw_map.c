/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 09:56:11 by jthuy             #+#    #+#             */
/*   Updated: 2020/09/30 17:23:41 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_backgraund(t_sdl *sdl, int mapwidth)
{
	int		cursor;
	char	fillflag = 1;

	cursor = 0;
	while (cursor < mapwidth * mapwidth)
	{
		PIXEL[cursor % mapwidth + WIDTH * (cursor / mapwidth)] = BACKCOLOR;
		cursor += 1;
	}
}

void	draw_contur(t_sdl *sdl, t_vlist *head, t_map *map)
{
	t_vlist		*cursor;

	cursor = head;
	while (1)
	{
		while (cursor->next && cursor->next->data)
		{
			map->scale_vert[0][X] = cursor->crd[X] * SCALER;
			map->scale_vert[0][Y] = cursor->crd[Y] * SCALER;
			map->scale_vert[1][X] = cursor->next->crd[X] * SCALER;
			map->scale_vert[1][Y] = cursor->next->crd[Y] * SCALER;
			draw_line(sdl, map->scale_vert[0], map->scale_vert[1]);
			cursor = cursor->next;
		}
		// NEED UNCOMMENT TO CLOSE CONTUR
		map->scale_vert[0][X] = cursor->crd[X] * SCALER;
		map->scale_vert[0][Y] = cursor->crd[Y] * SCALER;
		map->scale_vert[1][X] = head->crd[X] * SCALER;
		map->scale_vert[1][Y] = head->crd[Y] * SCALER;
		draw_line(sdl, map->scale_vert[0], map->scale_vert[1]);
		if (!cursor->next)
			return ;
		head = cursor->next->next;
		cursor = head;
	}
}

void	draw_player(t_sdl *sdl, t_player *player)
{
	int		cursor[2];
	int		limit[2];

	player->pastcrd[X] = player->crd[X] - 1;
	player->pastcrd[Y] = player->crd[Y] - 1;
	
	cursor[Y] = player->crd[Y] - 1;
	limit[Y] = 0;
	while (limit[Y] < 3)
	{
		cursor[X] = player->crd[X] - 1;
		limit[X] = 0;
		while (limit[X] < 3)
		{
			PIXEL[cursor[X] + limit[X] + WIDTH * (cursor[Y] + limit[Y])] = PLAYCOLOR;
			limit[X] += 1;
		}
		limit[Y] += 1;
	}
}

void	clear_player(t_sdl *sdl, t_player *player)
{
	int		limit[2];
	
	limit[Y] = 0;
	while (limit[Y] < 3)
	{
		limit[X] = 0;
		while (limit[X] < 3)
		{
			PIXEL[player->pastcrd[X] + limit[X] + WIDTH * (player->pastcrd[Y] + limit[Y])] = BACKCOLOR;
			limit[X] += 1;
		}
		limit[Y] += 1;
	}
	
}