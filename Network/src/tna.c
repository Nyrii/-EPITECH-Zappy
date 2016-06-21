/*
** tna.c for tna in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:01:14 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 12:16:09 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"
#include "replies.h"

int		tna(t_server *srv, t_client *cl)
{
  unsigned int	i;
  t_team	*t;

  i = 0;
  if (!srv || !cl)
    {
      fprintf(stderr, INTERNAL_ERR);
      return (-1);
    }
  while (i < list_get_size(srv->data.teams))
    {
      if ((t = list_get_elem_at_position(srv->data.teams, i)) != NULL)
	{
	  if ((dprintf(cl->sock, TNA, t->name)) == -1)
	    return (fprintf(stderr, ERR_PRINTF), -1);
	}
      i++;
    }
  return (0);
}
