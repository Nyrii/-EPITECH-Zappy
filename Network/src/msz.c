/*
** msz.c for msz in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:00:27 2016 Nyrandone Noboud-Inpeng
** Last update Fri Jun 10 18:08:18 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"

int		msz(t_server *srv, t_client *cl)
{
  if (dprintf(cl->sock, "msz %d %d\r\n", srv->data.world_x,
      srv->data.world_y) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
