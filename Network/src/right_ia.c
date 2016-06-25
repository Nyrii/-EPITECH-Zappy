/*
** right_ia.c for right_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Thu Jun  9 21:46:42 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:40:26 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "enum.h"
#include "replies.h"
#include "errors.h"

int		right_ia(t_server *server, t_player *player)
{
  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (player->orientation + 90 > LEFT)
    player->orientation = TOP;
  else
    player->orientation += 90;
  if (store_answer_p(player, strdup(OK), 0) == -1)
    return (fprintf(stderr, ERR_BUFFER), -1);
  return (ppo_ia(server, player));
}
