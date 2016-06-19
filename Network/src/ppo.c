/*
** ppo.c for ppo in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:02:42 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 14:11:29 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		ppo_ia(t_server *server, t_player *player)
{
  char		buffer[80];
  int		orientation;

  orientation = player->orientation == TOP ? 1 :
      player->orientation == RIGHT ? 2 : player->orientation == BOTTOM ? 3 : 4;
  if (memset(buffer, 0, 80) == NULL
      || snprintf(buffer, 80, PPO,
		  player->id, player->x, player->y, orientation) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}

int		ppo(t_server *server, t_client *graphic)
{
  (void)server;
  (void)graphic;
  return (0);
}
