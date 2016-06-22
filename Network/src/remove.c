/*
** simple_list.c for  in /home/empoci_k/rendu_tek2/piscine_cpp_d02a/ex00
**
** Made by Kévin Empociello
** Login   <empoci_k@epitech.net>
**
** Started on  Thu Jan  7 15:14:51 2016 Kévin Empociello
** Last update Sat Jun 11 19:32:36 2016 Kevin Empociello
*/

#include <string.h>
#include "server.h"

int		remove_player_from_srv(t_server *srv, t_team *t, t_player *pl)
{
  t_player	*p;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->all_players))
    {
      if ((p = list_get_elem_at_position(srv->all_players, i)) != NULL
	  && p->sock == pl->sock)
	if (list_del_elem_at_position(&srv->all_players, i) == FALSE)
	    return (-1);
	  i++;
    }
      i = 0;
    while (i < list_get_size(t->players))
	{
	  if ((p = list_get_elem_at_position(t->players, i)) != NULL
	      && p->sock == pl->sock)
	    if (list_del_elem_at_position(&t->players, i) == FALSE)
		return (-1);
	      i++;
	}
      return (0);
}

int		remove_client_from_queue(t_server *srv, t_client *cl)
{
  t_client	*c;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->queue_clients))
    {
      if ((c = list_get_elem_at_position(srv->queue_clients, i)) != NULL
	  && c->sock == cl->sock)
	if (list_del_elem_at_position(&srv->queue_clients, i) == FALSE)
	    return (-1);
      i++;
    }
  return (0);
}
