/*
** fork_ia.c for fork_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:29 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:10:52 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		fork_ia(t_server *server, t_player *player)
{
  t_egg		*egg;

  if (!server || !player)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  if ((egg = new_egg(server, player)) == NULL)
    return (-1);
  egg->player_id = player->id;
  if (list_add_elem_at_back(&server->data.eggs, egg) == FALSE)
    {
      fprintf(stderr, ERR_MALLOC);
      return (-1);
    }
  if (pfk(server, player) == -1)
    return (-1);
  player->fork.egg = egg;
  // Timer;
  // wait le timer
  return (0);
}
