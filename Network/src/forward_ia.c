/*
** forward_ia.c for forward_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:46:10 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 16:24:25 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "errors.h"
#include "enum.h"

int		forward_ia(t_server *server, t_player *player)
{
  int		x;
  int		y;

  (void)server;
  x = player->x;
  y = player->y;
  if (!server->data.map
      || !server->data.map[y] || !server->data.map[y][x])
    return (fprintf(stderr, ERR_POS_MAP), -1);
  if (player->orientation == TOP || player->orientation == BOTTOM)
    {
      if (player->orientation == TOP)
	y = y - 1 >= 0 ? (y - 1) : (server->data.world_y - 1);
      else
	y = y + 1 >= server->data.world_y ? 0 : (y + 1);
      player->y = y;
    }
  else
    {
      if (player->orientation == RIGHT)
	x = x + 1 >= server->data.world_x ? 0 : (x + 1);
      else
	x = x - 1 >= 0 ? (x - 1) : (server->data.world_x - 1);
      player->x = x;
    }
  // send message to ALL GRAPHIC CLIENTS and "ok" to the player
  return (0);
}
