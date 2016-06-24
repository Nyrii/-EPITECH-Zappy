/*
** tna.c for tna in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Fri Jun 10 18:01:14 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 18:26:11 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "errors.h"
#include "server.h"
#include "replies.h"

int		tna(t_server *srv, t_client *cl)
{
  unsigned int	i;
  t_team	*t;
  char		buffer[4096];

  i = -1;
  if (!srv || !cl)
    return (fprintf(stderr, INTERNAL_ERR), -1);
  while (++i < list_get_size(srv->data.teams))
    {
      if ((t = list_get_elem_at_position(srv->data.teams, i)) != NULL)
	{
	  if (memset(buffer, 0, 4096) == NULL
	      || snprintf(buffer, 4096, TNA, t->name) == -1)
	    {
	      fprintf(stderr, ERR_MEMSET);
	      fprintf(stderr, ERR_PRINTF);
	      return (-1);
	    }
	  if (store_answer_c(cl, buffer, 0) == -1)
	    return (fprintf(stderr, ERR_BUFFER), -1);
	}
    }
  return (0);
}
