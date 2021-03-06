/*
** pgt.c for pgt in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:54:36 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 25 16:49:04 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pgt(t_server *server, t_player *player, int const index)
{
  char		buffer[40];

  if (!server || !player)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 40) == NULL
      || snprintf(buffer, 40, PGT, player->id, index) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, strdup(buffer)));
}
