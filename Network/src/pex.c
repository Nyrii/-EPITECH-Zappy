/*
** pex.c for pex in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:51:07 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 15:52:17 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pex(t_server *server, t_player *player)
{
  char		buffer[20];

  if (memset(buffer, 0, 20) == NULL
      || snprintf(buffer, 20, PEX, player->id) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}
