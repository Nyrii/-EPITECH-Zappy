/*
** tna.c for tna in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:01:14 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 19 13:43:41 2016 Nyrandone Noboud-Inpeng
*/

#include "errors.h"
#include "server.h"
#include "replies.h"

int		tna(t_server *srv, t_client *cl)
{
  unsigned int	i;
  t_team	*t;

  i = 0;
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
