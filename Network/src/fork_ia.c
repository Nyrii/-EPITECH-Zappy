/*
** fork_ia.c for fork_ia in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 15:43:29 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 14 22:46:14 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "replies.h"
#include "errors.h"

int		fork_ia(t_server *server, t_player *player)
{
  t_egg		*egg;

  if ((egg = new_egg(server, player)) == NULL)
    return (-1);
  if (list_add_elem_at_back(&server->data.eggs, egg) == FALSE)
    {
      fprintf(stderr, ERR_MALLOC);
      return (-1);
    }
  if (dprintf(player->sock, OK) == -1)
    {
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  return (0);
}
