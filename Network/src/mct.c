/*
** mct.c for mct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 11 16:14:55 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:09:52 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"
#include "replies.h"

int		mct(t_server *srv, t_client *cl)
{
  char		*tmp;
  int		x;
  int		y;

  x = 0;
  if (!srv || !cl)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  while (x < srv->data.world_x)
    {
      y = 0;
      while (y < srv->data.world_y)
	{
	  if ((tmp = bct(srv->data.map, y, x)) == NULL)
	    return (-1);
	  dprintf(cl->sock, MSG, tmp);
	  free(tmp);
	  y++;
	}
      x++;
    }
  return (0);
}
