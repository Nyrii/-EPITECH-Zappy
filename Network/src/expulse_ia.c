/*
** expulse_ia.c for expulse_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:42:31 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 22:58:41 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		expulse_ia(t_server *server, t_player *player)
{
  t_list	*tmp;
  int		x;
  int		y;

  tmp = get_players_at_pos(&server->data, player->y, player->x);
  x = player->x;
  y = player->y;
  player->orientation == TOP ? (y -= 1) :
      player->orientation == BOTTOM ? (y += 1) : 0;
  player->orientation == RIGHT ? (x += 1) :
      player->orientation == LEFT ? (x -= 1) : 0;
  x = x >= server->data.world_x ? 0 : x < 0 ? server->data.world_x - 1 : x;
  y = y >= server->data.world_y ? 0 : y < 0 ? server->data.world_y - 1 : x;
  while (tmp != NULL)
    {
      if (((t_player *)((*tmp)->value))->sock != player->sock)
	{
	  ((t_player *)((*tmp)->value))->x = x;
  	  ((t_player *)((*tmp)->value))->y = y;
	}
      *tmp = (*tmp)->next;
    }
  return (0);
}
