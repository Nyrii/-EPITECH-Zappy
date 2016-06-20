/*
** pbc.c for pbc in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Mon Jun 20 15:34:58 2016 Nyrandone Noboud-Inpeng
** Last update Mon Jun 20 15:44:08 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"
#include "replies.h"

int		pbc(t_server *server, t_player *player)
{
  char		buffer[20 + strlen(server->params)];

  if (memset(buffer, 0, 20 + strlen(server->params)) == NULL
	      || snprintf(buffer, 20 + strlen(server->params),
			  PBC, player->id, server->params) == -1)
    return (fprintf(stderr, ERR_MEMSET), -1);
  return (send_all_graphics(server, buffer));
}
