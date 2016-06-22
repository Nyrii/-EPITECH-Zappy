/*
** mct.c for mct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 11 16:14:55 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 13:29:24 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "replies.h"
#include "errors.h"

int		mct(t_server *srv, t_client *cl)
{
  char		*tmp;
  int		x;
  int		y;
  char		buffer[4096];

  x = 0;
  if (!srv || !cl)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  while (x < srv->data.world_x)
    {
      y = 0;
      while (y < srv->data.world_y)
	{
	  if ((tmp = bct(srv->data.map, y, x)) == NULL)
	    return (-1);
	  if (memset(buffer, 0, 4096) == NULL
	      || snprintf(buffer, 4096, MSG, tmp) == -1)
	    return (fprintf(stderr, ERR_MEMSET), -1);
	  dprintf(cl->sock, "%s", buffer);
	  free(tmp);
	  y++;
	}
      x++;
    }
  return (0);
}
