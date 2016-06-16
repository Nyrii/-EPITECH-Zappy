/*
** incantation_ia.c for incantation in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:11 2016 Nyrandone Noboud-Inpeng
** Last update Thu Jun 16 15:48:06 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		incantation_ia(t_server *server, t_player *player)
{
  int		pos[2];
  int		i;
  int		level;

  i = -1;
  level = player->level;
  pos[0] = player->y;
  pos[1] = player->x;
  if (is_elevation_legit(&server->data, level, pos) == 0)
    {
      player->level += 1;
      while (server->data.map[pos[0]][pos[1]][++i] != -1)
	server->data.map[pos[0]][pos[1]][i] -= server->data.resources[level][i];
      // check victory;
      return (0);
    }
  return (0);
}
