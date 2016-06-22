/*
** sgt.c for sgt in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nekfeu
** Login   <empoci_k@epitech.eu>
**
** Started on  Fri Jun 10 18:00:27 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 13:56:14 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int		sgt(t_server *server, t_client *graphic)
{
  char		buffer[30];

  if (!server || !graphic)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  if (memset(buffer, 0, 30) == NULL
      || snprintf(buffer, 30, SGT, server->data.delay) == -1)
    {
      fprintf(stderr, ERR_MEMSET);
      fprintf(stderr, ERR_PRINTF);
      return (-1);
    }
  if (dprintf(graphic->sock, "%s", buffer) == -1)
    return (fprintf(stderr, ERR_PRINTF), -1);
  return (0);
}
