/*
** msz.c for msz in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:00:27 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 13:37:19 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"
#include "replies.h"

int		msz(t_server *srv, t_client *cl)
{
  if (dprintf(cl->sock, MSZ, srv->data.world_x,
      srv->data.world_y) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
