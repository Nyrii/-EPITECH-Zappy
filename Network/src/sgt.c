/*
** sgt.c for sgt in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nekfeu
** Login   <empoci_k@epitech.eu>
**
** Started on  Fri Jun 10 18:00:27 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 18:17:44 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"
#include "replies.h"

int		sgt(t_server *server, t_client *graphic)
{
  if (dprintf(graphic->sock, SGT, server->data.delay) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
