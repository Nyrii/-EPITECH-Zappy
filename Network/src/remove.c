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

int		remove_client_from_queue(t_server *srv, t_client *cl)
{
  t_client	*c;
  unsigned int	i;

  i = 0;
  while (i < list_get_size(srv->queue_clients))
    {
      if ((c = list_get_elem_at_position(srv->queue_clients, i)) != NULL
	  && c == cl)
	if (list_del_elem_at_position(&srv->queue_clients, i) == FALSE)
	    return (-1);
      i++;
    }
  return (0);
}
