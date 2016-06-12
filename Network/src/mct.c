/*
** mct.c for mct in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Sat Jun 11 16:14:55 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 16:15:20 2016 Nyrandone Noboud-Inpeng
*/

#include "server.h"

int		mct(t_server *srv, t_client *cl)
{
  char		*tmp;
  int		x;
  int		y;

  x = 0;
  y = 0;
  while (x < srv->data.world_x)
    {
      y = 0;
      while (y < srv->data.world_y)
	{
	  if ((tmp = bct(srv->data.map, x, y)) == NULL)
	    return (-1);
	  dprintf(cl->sock, "%s\r\n", tmp);
	  free(tmp);
	  y++;
	}
      x++;
    }
  return (0);
}
