/*
** broadcast_init.c for braodcast_init in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun 14 20:53:23 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 13:23:00 2016 Nyrandone Noboud-Inpeng
*/

#include <math.h>
#include "server.h"

void		init_calculs(t_data data, int *pos, t_player *target)
{
  pos[0] = target->y - data.world_y;
  pos[1] = target->x;
  pos[2] = target->y - data.world_y;
  pos[3] = target->x - data.world_x;
  pos[4] = target->y;
  pos[5] = target->x - data.world_x;
  pos[6] = target->y + data.world_y;
  pos[7] = target->x - data.world_x;
  pos[8] = target->y + data.world_y;
  pos[9] = target->x;
  pos[10] = target->y + data.world_y;
  pos[11] = target->x + data.world_x;
  pos[12] = target->y;
  pos[13] = target->x + data.world_x;
  pos[14] = target->y - data.world_y;
  pos[15] = target->x + data.world_x;
  pos[16] = target->y;
  pos[17] = target->x;
  pos[18] = -1;
}

int		get_best_tile(int *perimeter_dest, t_player *player)
{
  int		i;
  int		save;
  float		distance;

  distance = -1;
  save = 0;
  i = 0;
  while (perimeter_dest[i] != -1)
    {
      if (distance == -1
	  || distance > sqrt(pow(perimeter_dest[i] - player->y, 2)
			     + pow(perimeter_dest[i + 1] - player->x, 2)))
	{
	  distance = sqrt(pow(perimeter_dest[i] - player->y, 2)
			  + pow(perimeter_dest[i + 1] - player->x, 2));
	  if (i == 16)
	    save = 0;
	  else
	    save = i / 2 + 1;
	}
      i += 2;
    }
  return (save);
}
