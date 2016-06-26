/*
** forward_ia.c for forward_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:46:10 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:34:16 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "enum.h"
#include "replies.h"

int	send_answer(t_server *server, t_player *player)
{
  if (store_answer_p(player, strdup(OK), 0) == -1)
    {
      fprintf(stderr, ERR_BUFFER);
      return (-1);
    }
  return (ppo_ia(server, player));
}

int		forward_ia(t_server *server, t_player *player)
{
  int		x;
  int		y;

  x = player->x;
  y = player->y;
  if (!server || !player || !server->data.map
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
  return (send_answer(server, player));
}
