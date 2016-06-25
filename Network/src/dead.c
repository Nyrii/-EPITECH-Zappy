/*
** dead.c for dead in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 24 16:06:57 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 18:11:56 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		dead_ia(t_server *server, t_player *player)
{
  if (store_answer_p(player, strdup(DEAD), 0) == -1
      || pdi(server, player) == -1)
    {
      fprintf(stderr, ERR_BUFFER);
      return (-1);
    }
  player->off = 1;
  return (0);
}

int		dead(UNUSED t_server *server, t_client *graphic)
{
  if (store_answer_c(graphic, strdup(DEAD), 0) == -1)
    {
      fprintf(stderr, ERR_BUFFER);
      return (-1);
    }
  graphic->off = 1;
  return (0);
}
