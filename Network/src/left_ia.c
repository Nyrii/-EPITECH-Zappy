/*
** left_ia.c for left_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:47:42 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:21:58 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "enum.h"
#include "errors.h"
#include "replies.h"

int		left_ia(t_server *server, t_player *player)
{
  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (player->orientation - 90 < TOP)
    player->orientation = LEFT;
  else
    player->orientation -= 90;
  if (dprintf(player->sock, OK) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (ppo_ia(server, player));
}
